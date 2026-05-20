#import <Cocoa/Cocoa.h>
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

extern "C" void ime_update_cursor(void* glfwwin) {
    GLFWwindow* win = (GLFWwindow*)glfwwin;
    NSWindow* nswin = glfwGetCocoaWindow(win);
    NSView* view = [nswin contentView];
    NSTextInputContext* ctx = [view inputContext];
    if (ctx) [ctx invalidateCharacterCoordinates];
}