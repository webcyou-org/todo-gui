const std = @import("std");

pub fn build(b: *std.Build) void {
    const target   = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const sdl2_inc  = "/opt/homebrew/Cellar/sdl2/2.32.10/include/SDL2";
    const sdl2_lib  = "/opt/homebrew/Cellar/sdl2/2.32.10/lib";
    const nk_vendor = "vendor";

    const mod = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target    = target,
        .optimize  = optimize,
        .link_libc = true,
    });

    mod.addIncludePath(.{ .cwd_relative = nk_vendor });
    mod.addIncludePath(.{ .cwd_relative = sdl2_inc  });
    mod.addIncludePath(b.path("src"));

    mod.addLibraryPath(.{ .cwd_relative = sdl2_lib });
    mod.linkSystemLibrary("SDL2",        .{});
    mod.linkFramework("Cocoa",           .{});
    mod.linkFramework("IOKit",           .{});
    mod.linkFramework("CoreVideo",       .{});
    mod.linkFramework("CoreAudio",       .{});
    mod.linkFramework("AudioToolbox",    .{});
    mod.linkFramework("Carbon",          .{});
    mod.linkFramework("ForceFeedback",   .{});
    mod.linkFramework("Metal",           .{});

    mod.addCSourceFiles(.{
        .files = &.{ "src/nuklear_impl.c", "src/nk_app.c" },
        .flags = &.{"-std=c99"},
    });

    const exe = b.addExecutable(.{ .name = "todo", .root_module = mod });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| run_cmd.addArgs(args);
    b.step("run", "Run the app").dependOn(&run_cmd.step);
}