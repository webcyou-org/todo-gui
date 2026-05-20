const std = @import("std");

pub fn build(b: *std.Build) void {
    const target   = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const glfw_inc = "/opt/homebrew/Cellar/glfw/3.4/include";
    const glfw_lib = "/opt/homebrew/Cellar/glfw/3.4/lib";

    // zgui core without backend (we compile the backends ourselves below)
    const zgui_dep = b.dependency("zgui", .{
        .target   = target,
        .optimize = optimize,
        .backend  = @as(@import("zgui").Backend, .no_backend),
    });

    const mod = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target     = target,
        .optimize   = optimize,
        .link_libc  = true,
        .link_libcpp = true,
    });

    mod.addImport("zgui", zgui_dep.module("root"));
    mod.linkLibrary(zgui_dep.artifact("imgui"));

    // GLFW
    mod.addIncludePath(.{ .cwd_relative = glfw_inc });
    mod.addLibraryPath(.{ .cwd_relative = glfw_lib });
    mod.linkSystemLibrary("glfw", .{});

    // macOS frameworks
    mod.linkFramework("OpenGL",          .{});
    mod.linkFramework("Cocoa",           .{});
    mod.linkFramework("IOKit",           .{});
    mod.linkFramework("CoreVideo",       .{});
    mod.linkFramework("CoreFoundation",  .{});

    // Include paths for imgui backends
    mod.addIncludePath(zgui_dep.path("libs"));
    mod.addIncludePath(zgui_dep.path("libs/imgui"));
    mod.addIncludePath(zgui_dep.path("libs/imgui/backends"));

    // Compile imgui GLFW+OpenGL3 backends without IMGUI_IMPL_OPENGL_LOADER_CUSTOM.
    // This lets imgui use its embedded gl3w loader (dlopen on macOS) which is the
    // correct approach for systems without zopengl.
    const backend_flags = &[_][]const u8{
        "-std=c++17",
        "-DGL_SILENCE_DEPRECATION",
        "-fno-sanitize=undefined",
        "-Wno-elaborated-enum-base",
        // Export backend API with C linkage so Zig extern fn can resolve symbols
        "-DIMGUI_IMPL_API=extern \"C\"",
        // Must match zgui's libimgui.a compilation flags to keep ImGuiIO layout consistent
        "-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS",
    };

    mod.addCSourceFile(.{
        .file  = zgui_dep.path("libs/imgui/backends/imgui_impl_glfw.cpp"),
        .flags = backend_flags,
    });
    mod.addCSourceFile(.{
        .file  = zgui_dep.path("libs/imgui/backends/imgui_impl_opengl3.cpp"),
        .flags = backend_flags,
    });
    mod.addCSourceFile(.{
        .file  = b.path("src/ime_mac.mm"),
        .flags = &[_][]const u8{ "-fno-sanitize=undefined" },
    });

    const exe = b.addExecutable(.{ .name = "todo", .root_module = mod });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| run_cmd.addArgs(args);
    b.step("run", "Run the app").dependOn(&run_cmd.step);
}