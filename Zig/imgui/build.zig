const std = @import("std");

pub fn build(b: *std.Build) void {
    const target   = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const glfw_inc  = "/opt/homebrew/Cellar/glfw/3.4/include";
    const glfw_lib  = "/opt/homebrew/Cellar/glfw/3.4/lib";
    const imgui_dir = "vendor";
    const imgui_be  = "vendor/backends";

    const mod = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target     = target,
        .optimize   = optimize,
        .link_libc  = true,
        .link_libcpp = true,
    });

    mod.addIncludePath(.{ .cwd_relative = imgui_dir });
    mod.addIncludePath(.{ .cwd_relative = imgui_be  });
    mod.addIncludePath(.{ .cwd_relative = glfw_inc  });
    mod.addIncludePath(b.path("src"));

    mod.addLibraryPath(.{ .cwd_relative = glfw_lib });
    mod.linkSystemLibrary("glfw",    .{});
    mod.linkFramework("OpenGL",          .{});
    mod.linkFramework("Cocoa",           .{});
    mod.linkFramework("IOKit",           .{});
    mod.linkFramework("CoreVideo",       .{});
    mod.linkFramework("CoreFoundation",  .{});

    const cpp_flags = &[_][]const u8{ "-std=c++17", "-DGL_SILENCE_DEPRECATION" };
    const mm_flags  = &[_][]const u8{ "-std=c++17", "-DGL_SILENCE_DEPRECATION",
                                       "-DGLFW_EXPOSE_NATIVE_COCOA", "-fobjc-arc" };

    mod.addCSourceFiles(.{
        .files = &.{
            imgui_dir ++ "/imgui.cpp",
            imgui_dir ++ "/imgui_draw.cpp",
            imgui_dir ++ "/imgui_tables.cpp",
            imgui_dir ++ "/imgui_widgets.cpp",
            imgui_be  ++ "/imgui_impl_glfw.cpp",
            imgui_be  ++ "/imgui_impl_opengl3.cpp",
            "src/imgui_app.cpp",
        },
        .flags = cpp_flags,
    });

    mod.addCSourceFiles(.{
        .files = &.{ "src/ime_mac.mm" },
        .flags = mm_flags,
    });

    const exe = b.addExecutable(.{ .name = "todo", .root_module = mod });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| run_cmd.addArgs(args);
    b.step("run", "Run the app").dependOn(&run_cmd.step);
}
