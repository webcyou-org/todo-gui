const std = @import("std");

pub fn build(b: *std.Build) void {
    const target   = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const wx_inc1 = "/opt/homebrew/lib/wx/include/osx_cocoa-unicode-3.3";
    const wx_inc2 = "/opt/homebrew/include/wx-3.3";
    const wx_lib  = "/opt/homebrew/lib";

    const mod = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target      = target,
        .optimize    = optimize,
        .link_libc   = true,
        .link_libcpp = true,
    });

    mod.addIncludePath(.{ .cwd_relative = wx_inc1 });
    mod.addIncludePath(.{ .cwd_relative = wx_inc2 });
    mod.addIncludePath(b.path("src"));

    mod.addLibraryPath(.{ .cwd_relative = wx_lib });

    mod.linkFramework("IOKit",        .{});
    mod.linkFramework("Carbon",       .{});
    mod.linkFramework("Cocoa",        .{});
    mod.linkFramework("QuartzCore",   .{});
    mod.linkFramework("AudioToolbox", .{});
    mod.linkFramework("OpenGL",       .{});

    mod.linkSystemLibrary("wx_osx_cocoau_xrc-3.3",  .{});
    mod.linkSystemLibrary("wx_osx_cocoau_html-3.3", .{});
    mod.linkSystemLibrary("wx_osx_cocoau_qa-3.3",   .{});
    mod.linkSystemLibrary("wx_osx_cocoau_core-3.3", .{});
    mod.linkSystemLibrary("wx_baseu_xml-3.3",        .{});
    mod.linkSystemLibrary("wx_baseu_net-3.3",        .{});
    mod.linkSystemLibrary("wx_baseu-3.3",            .{});

    const cpp_flags = &[_][]const u8{
        "-std=c++17",
        "-D_FILE_OFFSET_BITS=64",
        "-DwxDEBUG_LEVEL=0",
        "-DWXUSINGDLL",
        "-D__WXMAC__",
        "-D__WXOSX__",
        "-D__WXOSX_COCOA__",
    };

    mod.addCSourceFiles(.{
        .files = &.{
            "src/wx_app.cpp",
            "src/widgets/todo_input.cpp",
            "src/widgets/tab_menu.cpp",
            "src/widgets/todo_item.cpp",
        },
        .flags = cpp_flags,
    });

    const exe = b.addExecutable(.{ .name = "todo", .root_module = mod });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| run_cmd.addArgs(args);
    b.step("run", "Run the app").dependOn(&run_cmd.step);
}