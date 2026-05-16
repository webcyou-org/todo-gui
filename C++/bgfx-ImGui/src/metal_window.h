#pragma once
// Creates a CAMetalLayer attached to the NSWindow's content view.
// Returns the CAMetalLayer* as void* (to avoid ObjC types in headers).
void* metal_create_layer(void* nswindow, int width, int height);