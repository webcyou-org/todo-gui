const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const mod = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    mod.addIncludePath(.{ .cwd_relative = "/opt/homebrew/Cellar/raylib/5.5/include" });
    mod.addLibraryPath(.{ .cwd_relative = "/opt/homebrew/Cellar/raylib/5.5/lib" });
    mod.linkSystemLibrary("raylib", .{});
    mod.linkFramework("OpenGL", .{});
    mod.linkFramework("Cocoa", .{});
    mod.linkFramework("IOKit", .{});
    mod.linkFramework("CoreVideo", .{});

    const exe = b.addExecutable(.{
        .name = "todo",
        .root_module = mod,
    });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| run_cmd.addArgs(args);

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}