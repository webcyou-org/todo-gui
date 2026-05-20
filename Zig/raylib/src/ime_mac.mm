#import <Cocoa/Cocoa.h>
#import <objc/runtime.h>

static NSRect g_ime_rect;

static NSRect swizzled_firstRect(id self, SEL _cmd, NSRange range, NSRangePointer actualRange) {
    if (actualRange) *actualRange = range;
    if (g_ime_rect.size.height > 0) return g_ime_rect;
    NSWindow *win = [(NSView *)self window];
    NSRect f = win ? [win frame] : NSMakeRect(0, 0, 200, 200);
    return NSMakeRect(NSMinX(f) + 20, NSMinY(f) + 20, 1, 16);
}

extern "C" void ime_setup(void) {
    g_ime_rect = NSZeroRect;
    Class cls = NSClassFromString(@"GLFWContentView");
    if (!cls) { NSLog(@"[ime] GLFWContentView not found"); return; }
    SEL sel = @selector(firstRectForCharacterRange:actualRange:);
    Method m = class_getInstanceMethod(cls, sel);
    if (m) method_setImplementation(m, (IMP)swizzled_firstRect);

    dispatch_async(dispatch_get_main_queue(), ^{
        [NSApp activateIgnoringOtherApps:YES];
        NSWindow *win = [NSApp keyWindow] ?: [NSApp mainWindow];
        if (!win) return;
        NSTextInputContext *ctx = [[win contentView] inputContext];
        if (ctx) [ctx activate];
    });
}

// x,y = cursor top-left in raylib logical coords, h = line height
extern "C" void ime_set_cursor(float x, float y, float h) {
    NSWindow *win = [NSApp keyWindow] ?: [NSApp mainWindow];
    if (!win) return;
    NSView *view = [win contentView];
    CGFloat viewH = view.bounds.size.height;
    // Raylib y↓, NSView y↑ — flip the y axis
    NSPoint viewPt   = NSMakePoint(x, viewH - y - h);
    NSPoint winPt    = [view convertPoint:viewPt toView:nil];
    NSPoint screenPt = [win convertPointToScreen:winPt];
    g_ime_rect = NSMakeRect(screenPt.x, screenPt.y, 1.0, h);
    NSTextInputContext *ctx = [view inputContext];
    if (ctx) [ctx invalidateCharacterCoordinates];
}

// Call once per frame to let the NSRunLoop deliver IME insertText: messages
extern "C" void ime_tick(void) {
    [[NSRunLoop mainRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1.0 / 240.0]];
}