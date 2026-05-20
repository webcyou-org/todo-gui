#import <Cocoa/Cocoa.h>
#include <CoreFoundation/CoreFoundation.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

extern "C" void ime_setup_window(void* glfwwin) {
    GLFWwindow* win = (GLFWwindow*)glfwwin;
    NSWindow* nswin = glfwGetCocoaWindow(win);

    dispatch_async(dispatch_get_main_queue(), ^{
        [NSApp activateIgnoringOtherApps:YES];
        [nswin makeKeyAndOrderFront:nil];
        NSTextInputContext* ctx = [NSTextInputContext currentInputContext];
        if (ctx) [ctx activate];
    });
}

// Drain pending IME Mach port messages before glfwPollEvents so that
// characters posted by the IME are in the NSEvent queue when GLFW reads it.
extern "C" void ime_drain_runloop() {
    while (CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.0, true) == kCFRunLoopRunHandledSource) {}
}