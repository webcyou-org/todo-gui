const std = @import("std");

pub fn build(b: *std.Build) void {
    const target   = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const qt_lib     = "/opt/homebrew/lib";
    const qt_mkspecs = "/opt/homebrew/share/qt/mkspecs/macx-clang";

    const mod = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target      = target,
        .optimize    = optimize,
        .link_libc   = true,
        .link_libcpp = true,
    });

    // Qt framework headers
    mod.addIncludePath(.{ .cwd_relative = qt_lib ++ "/QtWidgets.framework/Headers" });
    mod.addIncludePath(.{ .cwd_relative = qt_lib ++ "/QtWidgets.framework" });
    mod.addIncludePath(.{ .cwd_relative = qt_lib ++ "/QtGui.framework/Headers" });
    mod.addIncludePath(.{ .cwd_relative = qt_lib ++ "/QtGui.framework" });
    mod.addIncludePath(.{ .cwd_relative = qt_lib ++ "/QtCore.framework/Headers" });
    mod.addIncludePath(.{ .cwd_relative = qt_lib ++ "/QtCore.framework" });
    mod.addIncludePath(.{ .cwd_relative = qt_mkspecs });
    mod.addIncludePath(b.path("src"));

    // Qt frameworks
    mod.addFrameworkPath(.{ .cwd_relative = qt_lib });
    mod.linkFramework("QtWidgets", .{});
    mod.linkFramework("QtGui", .{});
    mod.linkFramework("QtCore", .{});

    const cpp_flags = &[_][]const u8{
        "-std=c++17",
        "-DQT_WIDGETS_LIB",
        "-DQT_GUI_LIB",
        "-DQT_CORE_LIB",
        "-Wno-deprecated-declarations",
    };

    mod.addCSourceFiles(.{
        .files = &.{ "src/qt_app.cpp" },
        .flags = cpp_flags,
    });

    const exe = b.addExecutable(.{ .name = "todo", .root_module = mod });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| run_cmd.addArgs(args);
    b.step("run", "Run the app").dependOn(&run_cmd.step);
}