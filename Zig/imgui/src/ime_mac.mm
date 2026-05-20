#import <Cocoa/Cocoa.h>
#import <objc/runtime.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "imgui.h"

// Screen-space rect of the active text cursor (macOS coords, Y=0 at bottom).
static NSRect g_ime_cursor_rect  = NSZeroRect;
static bool   g_ime_cursor_valid = false; // NSIsEmptyRect is true for width=0 rects; use a flag instead

// ── firstRectForCharacterRange: swizzle ──────────────────────────────────────
// GLFW 3.4 returns a zero rect here, so Kotoeri can't place its candidate
// window and refuses to enter composition mode.
static NSRect swizzled_firstRect(id self, SEL _cmd, NSRange range, NSRangePointer actualRange)
{
    if (actualRange) *actualRange = range;
    if (g_ime_cursor_valid)
        return g_ime_cursor_rect;
    // Fallback: left edge of the window at a reasonable height
    NSWindow* win = [(NSView*)self window];
    NSRect f = win ? [win frame] : NSMakeRect(0, 0, 400, 30);
    return NSMakeRect(NSMinX(f) + 24, NSMinY(f) + 24, 0, 20);
}

// ── insertText:replacementRange: swizzle ─────────────────────────────────────
// Inject confirmed IME text directly into ImGui, bypassing GLFW's char-callback
// chain which can miss deliveries made while the run loop is active.
static void (*g_orig_insertText)(id, SEL, id, NSRange) = nullptr;

static void swizzled_insertText(id self, SEL _cmd, id aString, NSRange replacementRange)
{
    NSString* str = [aString isKindOfClass:[NSAttributedString class]]
        ? [(NSAttributedString*)aString string] : (NSString*)aString;

    ImGuiIO& io = ImGui::GetIO();
    for (NSUInteger i = 0; i < str.length; ) {
        NSRange r = [str rangeOfComposedCharacterSequenceAtIndex:i];
        uint32_t cp = 0;
        [str getBytes:&cp maxLength:4 usedLength:nil
             encoding:NSUTF32LittleEndianStringEncoding
              options:NSStringEncodingConversionAllowLossy
                range:r remainingRange:nil];
        if (cp) io.AddInputCharacter(cp);
        i += r.length;
    }
    // Do NOT call g_orig_insertText — that would double-inject via GLFW's char callback.
    // GLFW's internal hasMarkedText state is cleared by the setMarkedText:"" call
    // that Kotoeri always makes immediately after insertText:.
}

// ── setMarkedText:selectedRange:replacementRange: swizzle ────────────────────
// Keep GLFW's marked-text state accurate so hasMarkedText() works for
// ime_is_composing(). No character injection here — only the final insertText:
// delivers confirmed text.
static void (*g_orig_setMarkedText)(id, SEL, id, NSRange, NSRange) = nullptr;

static void swizzled_setMarkedText(id self, SEL _cmd, id aString, NSRange sel, NSRange rep)
{
    if (g_orig_setMarkedText) g_orig_setMarkedText(self, _cmd, aString, sel, rep);
}

// ── Install swizzles ─────────────────────────────────────────────────────────
static void install_swizzles()
{
    Class cls = NSClassFromString(@"GLFWContentView");
    if (!cls) { NSLog(@"[ime_mac] GLFWContentView not found"); return; }

    auto swizzle = [&](SEL sel, IMP replacement, IMP* orig_out) {
        Method m = class_getInstanceMethod(cls, sel);
        if (!m) { NSLog(@"[ime_mac] method not found: %s", sel_getName(sel)); return; }
        if (orig_out) *orig_out = method_getImplementation(m);
        method_setImplementation(m, replacement);
    };

    swizzle(@selector(firstRectForCharacterRange:actualRange:),
            (IMP)swizzled_firstRect, nullptr);
    swizzle(@selector(insertText:replacementRange:),
            (IMP)swizzled_insertText, (IMP*)&g_orig_insertText);
    swizzle(@selector(setMarkedText:selectedRange:replacementRange:),
            (IMP)swizzled_setMarkedText, (IMP*)&g_orig_setMarkedText);
}

// ── Platform_SetImeDataFn ────────────────────────────────────────────────────
static void ime_set_platform_data(ImGuiContext*, ImGuiViewport* vp, ImGuiPlatformImeData* data)
{
    GLFWwindow* win = (GLFWwindow*)vp->PlatformHandle;
    if (!win) return;
    NSWindow* nswin = glfwGetCocoaWindow(win);
    if (!nswin) return;

    if (data->WantVisible) {
        float x = data->InputPos.x;
        float y = data->InputPos.y + data->InputLineHeight;
        NSScreen* screen = [nswin screen] ?: [NSScreen mainScreen];
        CGFloat sh = [screen frame].size.height;
        NSPoint wp = [nswin convertPointToScreen:NSMakePoint(x, y)];
        g_ime_cursor_rect  = NSMakeRect(wp.x, sh - wp.y, 0.0, data->InputLineHeight);
        g_ime_cursor_valid = true;

        NSTextInputContext* ctx = [[nswin contentView] inputContext];
        if (ctx) [ctx invalidateCharacterCoordinates];
    } else {
        g_ime_cursor_valid = false;
    }
}

// ── Frame-level run loop step ────────────────────────────────────────────────
extern "C" void ime_run_until(double seconds)
{
    NSRunLoop* rl = [NSRunLoop mainRunLoop];
    [rl runUntilDate:[NSDate dateWithTimeIntervalSinceNow:seconds]];
    for (int i = 0; i < 8; i++) {
        if (![rl runMode:NSEventTrackingRunLoopMode
                beforeDate:[NSDate distantPast]]) break;
    }
}

// ── IME composition guard ────────────────────────────────────────────────────
extern "C" bool ime_is_composing()
{
    NSWindow* win = [NSApp keyWindow];
    if (!win) return false;
    NSView* view = [win contentView];
    if ([view respondsToSelector:@selector(hasMarkedText)])
        return [(id<NSTextInputClient>)view hasMarkedText];
    return false;
}

// ── Public entry point ───────────────────────────────────────────────────────
extern "C" void ime_setup_window(void* glfwwin)
{
    install_swizzles();

    GLFWwindow* win = (GLFWwindow*)glfwwin;
    NSWindow* nswin = glfwGetCocoaWindow(win);

    dispatch_async(dispatch_get_main_queue(), ^{
        [NSApp activateIgnoringOtherApps:YES];
        [nswin makeKeyAndOrderFront:nil];
        NSTextInputContext* ctx = [[nswin contentView] inputContext];
        if (ctx) [ctx activate];
    });

    ImGui::GetPlatformIO().Platform_SetImeDataFn = ime_set_platform_data;
}
