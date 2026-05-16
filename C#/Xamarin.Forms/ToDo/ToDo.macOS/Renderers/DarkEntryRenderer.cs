using AppKit;
using CoreGraphics;
using Foundation;
using ToDo.macOS.Renderers;
using Xamarin.Forms;
using Xamarin.Forms.Platform.MacOS;

[assembly: ExportRenderer(typeof(Entry), typeof(DarkEntryRenderer))]
namespace ToDo.macOS.Renderers
{
    public class DarkEntryRenderer : EntryRenderer
    {
        protected override void OnElementChanged(ElementChangedEventArgs<Entry> e)
        {
            base.OnElementChanged(e);
            if (Control == null) return;

            Control.BackgroundColor = NSColor.FromRgb(0x30, 0x30, 0x30);
            Control.TextColor = NSColor.White;
            Control.DrawsBackground = true;
            Control.Bordered = false;
            Control.WantsLayer = true;

            if (Control.Layer != null)
            {
                Control.Layer.BackgroundColor = new CGColor(0x30 / 255f, 0x30 / 255f, 0x30 / 255f);
                Control.Layer.CornerRadius = 4;
                Control.Layer.BorderWidth = 1;
                Control.Layer.BorderColor = new CGColor(0x5D / 255f, 0xC2 / 255f, 0xAF / 255f);
            }

            // Field editor (active editing NSTextView) も暗くする
            Control.Cell.BackgroundColor = NSColor.FromRgb(0x30, 0x30, 0x30);
        }
    }
}