using AppKit;
using Foundation;
using Xamarin.Forms;
using Xamarin.Forms.Platform.MacOS;

namespace ToDo.macOS
{
    [Register("AppDelegate")]
    public class AppDelegate : FormsApplicationDelegate
    {
        private NSWindow _window;

        public AppDelegate()
        {
            var style = NSWindowStyle.Closable | NSWindowStyle.Resizable | NSWindowStyle.Titled;
            var rect = new CoreGraphics.CGRect(200, 100, 800, 600);
            _window = new NSWindow(rect, style, NSBackingStore.Buffered, false);
            _window.Title = "ToDo";
            _window.MinSize = new CoreGraphics.CGSize(800, 600);
            _window.Center();
        }

        public override NSWindow MainWindow => _window;

        public override void DidFinishLaunching(NSNotification notification)
        {
            Forms.Init();
            LoadApplication(new global::ToDo.App());
            base.DidFinishLaunching(notification);
        }
    }
}