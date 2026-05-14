using System;
using Windows.UI;
using Windows.UI.Text;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Media;

namespace ToDo.Converters
{
    /// <summary>bool → FontWeight (Bold = active tab, Normal = inactive)</summary>
    public class BoolToFontWeightConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
            => (bool)value ? FontWeights.Bold : FontWeights.Normal;

        public object ConvertBack(object value, Type targetType, object parameter, string language)
            => throw new NotImplementedException();
    }

    /// <summary>bool → TextDecorations (Strikethrough when completed)</summary>
    public class BoolToTextDecorationsConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
            => (bool)value ? TextDecorations.Strikethrough : TextDecorations.None;

        public object ConvertBack(object value, Type targetType, object parameter, string language)
            => throw new NotImplementedException();
    }

    /// <summary>bool → Foreground (C_MUTED when completed, C_TEXT otherwise)</summary>
    public class BoolToForegroundConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return (bool)value
                ? new SolidColorBrush(Color.FromArgb(0xFF, 0x9B, 0x9B, 0x9B)) // C_MUTED
                : new SolidColorBrush(Color.FromArgb(0xFF, 0xD2, 0xD2, 0xD2)); // C_TEXT
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
            => throw new NotImplementedException();
    }

    /// <summary>bool → Checkbox fill (C_ACCENT when checked, Transparent otherwise)</summary>
    public class BoolToCheckboxFillConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return (bool)value
                ? new SolidColorBrush(Color.FromArgb(0xFF, 0x5D, 0xC2, 0xAF)) // C_ACCENT
                : new SolidColorBrush(Colors.Transparent);
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
            => throw new NotImplementedException();
    }

    /// <summary>bool → Checkbox stroke (C_ACCENT when checked, C_CB_BORDER otherwise)</summary>
    public class BoolToCheckboxStrokeConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return (bool)value
                ? new SolidColorBrush(Color.FromArgb(0xFF, 0x5D, 0xC2, 0xAF)) // C_ACCENT
                : new SolidColorBrush(Color.FromArgb(0xFF, 0xD9, 0xD9, 0xD9)); // C_CB_BORDER
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
            => throw new NotImplementedException();
    }
}