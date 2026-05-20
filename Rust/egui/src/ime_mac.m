#import <Cocoa/Cocoa.h>

// Activate the current NSTextInputContext so macOS routes IME (e.g. Kotoeri)
// events to this process. Must be called on the main thread (dispatch_async
// ensures this even when called from a non-main context).
void activate_ime(void) {
    dispatch_async(dispatch_get_main_queue(), ^{
        [NSApp activateIgnoringOtherApps:YES];
        NSTextInputContext* ctx = [NSTextInputContext currentInputContext];
        if (ctx) [ctx activate];
    });
}