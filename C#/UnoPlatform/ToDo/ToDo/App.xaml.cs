using System;
using System.Runtime.InteropServices;
using Microsoft.Extensions.Logging;
using Uno.Resizetizer;

namespace ToDo;

public partial class App : Application
{
    /// <summary>
    /// Initializes the singleton application object. This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    public App()
    {
        this.InitializeComponent();
    }

    protected Window? MainWindow { get; private set; }

    protected override void OnLaunched(LaunchActivatedEventArgs args)
    {
        MainWindow = new Window();
#if DEBUG
        MainWindow.EnableHotReload();
#endif

        if (MainWindow.Content is not Frame rootFrame)
        {
            rootFrame = new Frame();
            MainWindow.Content = rootFrame;
            rootFrame.NavigationFailed += OnNavigationFailed;
        }

        if (rootFrame.Content == null)
        {
            rootFrame.Navigate(typeof(MainPage), args.Arguments);
        }

        MainWindow.SetWindowIcon();
        MainWindow.Activate();

        if (OperatingSystem.IsMacOS())
        {
            try { MacOSResizeAndCenter(800, 600); } catch { }

            foreach (var ms in new[] { 300, 800, 1500 })
            {
                var delay = ms;
                _ = Task.Run(async () =>
                {
                    await Task.Delay(delay);
                    MainWindow.DispatcherQueue.TryEnqueue(() =>
                    {
                        try { MacOSResizeAndCenter(800, 600); } catch { }
                    });
                });
            }
        }
    }

    /// <summary>
    /// Invoked when Navigation to a certain page fails
    /// </summary>
    /// <param name="sender">The Frame which failed navigation</param>
    /// <param name="e">Details about the navigation failure</param>
    void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
    {
        throw new InvalidOperationException($"Failed to load {e.SourcePageType.FullName}: {e.Exception}");
    }

    // ── macOS AppKit P/Invoke でウィンドウをリサイズ＋センタリング ──────────

    [DllImport("libobjc.dylib", EntryPoint = "objc_getClass")]
    private static extern IntPtr ObjcGetClass(string name);

    [DllImport("libobjc.dylib", EntryPoint = "sel_registerName")]
    private static extern IntPtr SelRegisterName(string name);

    [DllImport("libobjc.dylib", EntryPoint = "objc_msgSend")]
    private static extern IntPtr ObjcMsgSend(IntPtr self, IntPtr sel);

    [DllImport("libobjc.dylib", EntryPoint = "objc_msgSend")]
    private static extern void ObjcMsgSendVoid(IntPtr self, IntPtr sel);

    [DllImport("libobjc.dylib", EntryPoint = "objc_msgSend")]
    private static extern void ObjcMsgSendSize(IntPtr self, IntPtr sel, MacSize size);

    [DllImport("libobjc.dylib", EntryPoint = "objc_msgSend")]
    private static extern void ObjcMsgSendPoint(IntPtr self, IntPtr sel, MacPoint point);

    [StructLayout(LayoutKind.Sequential)]
    private struct MacSize { public double Width, Height; }

    [StructLayout(LayoutKind.Sequential)]
    private struct MacPoint { public double X, Y; }

    [StructLayout(LayoutKind.Sequential)]
    private struct MacRect { public double X, Y, Width, Height; }

    [DllImport("libobjc.dylib", EntryPoint = "objc_msgSend")]
    private static extern IntPtr ObjcMsgSendIdx(IntPtr self, IntPtr sel, ulong idx);

    [DllImport("/System/Library/Frameworks/CoreGraphics.framework/CoreGraphics")]
    private static extern uint CGMainDisplayID();

    [DllImport("/System/Library/Frameworks/CoreGraphics.framework/CoreGraphics")]
    private static extern MacRect CGDisplayBounds(uint display);

    private static void MacOSResizeAndCenter(double width, double height)
    {
        var nsApp = ObjcMsgSend(ObjcGetClass("NSApplication"), SelRegisterName("sharedApplication"));

        // mainWindow → keyWindow → windows[0] の順でウィンドウを取得
        var win = ObjcMsgSend(nsApp, SelRegisterName("mainWindow"));
        if (win == IntPtr.Zero)
            win = ObjcMsgSend(nsApp, SelRegisterName("keyWindow"));
        if (win == IntPtr.Zero)
        {
            var arr = ObjcMsgSend(nsApp, SelRegisterName("windows"));
            if (arr != IntPtr.Zero)
            {
                var cnt = (long)ObjcMsgSend(arr, SelRegisterName("count"));
                if (cnt > 0)
                    win = ObjcMsgSendIdx(arr, SelRegisterName("objectAtIndex:"), 0UL);
            }
        }
        if (win == IntPtr.Zero) { Console.Error.WriteLine("[Center] no window found"); return; }

        ObjcMsgSendSize(win, SelRegisterName("setContentSize:"), new MacSize { Width = width, Height = height });

        var screen = CGDisplayBounds(CGMainDisplayID());
        var x = screen.X + (screen.Width - width) / 2;
        var y = screen.Y + (screen.Height - height) / 2;
        ObjcMsgSendPoint(win, SelRegisterName("setFrameOrigin:"), new MacPoint { X = x, Y = y });
    }

    /// <summary>
    /// Configures global Uno Platform logging
    /// </summary>
    public static void InitializeLogging()
    {
#if DEBUG
        // Logging is disabled by default for release builds, as it incurs a significant
        // initialization cost from Microsoft.Extensions.Logging setup. If startup performance
        // is a concern for your application, keep this disabled. If you're running on the web or
        // desktop targets, you can use URL or command line parameters to enable it.
        //
        // For more performance documentation: https://platform.uno/docs/articles/Uno-UI-Performance.html

        var factory = LoggerFactory.Create(builder =>
        {
#if __WASM__
            builder.AddProvider(new global::Uno.Extensions.Logging.WebAssembly.WebAssemblyConsoleLoggerProvider());
#elif __IOS__ || __MACCATALYST__
            builder.AddProvider(new global::Uno.Extensions.Logging.OSLogLoggerProvider());
#else
            builder.AddConsole();
#endif

            // Exclude logs below this level
            builder.SetMinimumLevel(LogLevel.Information);

            // Default filters for Uno Platform namespaces
            builder.AddFilter("Uno", LogLevel.Warning);
            builder.AddFilter("Windows", LogLevel.Warning);
            builder.AddFilter("Microsoft", LogLevel.Warning);

            // Generic Xaml events
            // builder.AddFilter("Microsoft.UI.Xaml", LogLevel.Debug );
            // builder.AddFilter("Microsoft.UI.Xaml.VisualStateGroup", LogLevel.Debug );
            // builder.AddFilter("Microsoft.UI.Xaml.StateTriggerBase", LogLevel.Debug );
            // builder.AddFilter("Microsoft.UI.Xaml.UIElement", LogLevel.Debug );
            // builder.AddFilter("Microsoft.UI.Xaml.FrameworkElement", LogLevel.Trace );

            // Layouter specific messages
            // builder.AddFilter("Microsoft.UI.Xaml.Controls", LogLevel.Debug );
            // builder.AddFilter("Microsoft.UI.Xaml.Controls.Layouter", LogLevel.Debug );
            // builder.AddFilter("Microsoft.UI.Xaml.Controls.Panel", LogLevel.Debug );

            // builder.AddFilter("Windows.Storage", LogLevel.Debug );

            // Binding related messages
            // builder.AddFilter("Microsoft.UI.Xaml.Data", LogLevel.Debug );
            // builder.AddFilter("Microsoft.UI.Xaml.Data", LogLevel.Debug );

            // Binder memory references tracking
            // builder.AddFilter("Uno.UI.DataBinding.BinderReferenceHolder", LogLevel.Debug );

            // DevServer and HotReload related
            // builder.AddFilter("Uno.UI.RemoteControl", LogLevel.Information);

            // Debug JS interop
            // builder.AddFilter("Uno.Foundation.WebAssemblyRuntime", LogLevel.Debug );
        });

        global::Uno.Extensions.LogExtensionPoint.AmbientLoggerFactory = factory;

#if HAS_UNO
        global::Uno.UI.Adapter.Microsoft.Extensions.Logging.LoggingAdapter.Initialize();
#endif
#endif
    }
}
