#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>

void* metal_create_layer(void* nswindow, int width, int height) {
    NSWindow* window = (__bridge NSWindow*)nswindow;
    NSView* view = window.contentView;

    view.wantsLayer = YES;

    CAMetalLayer* metalLayer = [CAMetalLayer layer];
    metalLayer.device = MTLCreateSystemDefaultDevice();
    metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    metalLayer.drawableSize = CGSizeMake(width, height);
    metalLayer.framebufferOnly = YES;

    view.layer = metalLayer;
    [metalLayer retain]; // keep alive for bgfx

    return (void*)metalLayer;
}