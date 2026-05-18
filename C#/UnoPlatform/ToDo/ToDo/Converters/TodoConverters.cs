using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Media;
using Windows.UI;
using Windows.UI.Text;

namespace ToDo.Converters;

public class BoolToCheckboxBackgroundConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, string language)
        => new SolidColorBrush(Color.FromArgb(0x00, 0x00, 0x00, 0x00));

    public object ConvertBack(object value, Type targetType, object parameter, string language)
        => throw new NotImplementedException();
}

public class BoolToCheckboxBorderBrushConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, string language)
        => new SolidColorBrush(Color.FromArgb(0xFF, 0xD9, 0xD9, 0xD9));

    public object ConvertBack(object value, Type targetType, object parameter, string language)
        => throw new NotImplementedException();
}

public class BoolToTextDecorationsConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, string language)
        => value is true ? TextDecorations.Strikethrough : TextDecorations.None;

    public object ConvertBack(object value, Type targetType, object parameter, string language)
        => throw new NotImplementedException();
}

public class BoolToVisibilityConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, string language)
        => value is true ? Microsoft.UI.Xaml.Visibility.Visible : Microsoft.UI.Xaml.Visibility.Collapsed;

    public object ConvertBack(object value, Type targetType, object parameter, string language)
        => throw new NotImplementedException();
}

public class BoolToCheckmarkForegroundConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, string language)
        => value is true
            ? new SolidColorBrush(Color.FromArgb(0xFF, 0x5D, 0xC2, 0xAF))
            : new SolidColorBrush(Color.FromArgb(0x00, 0x00, 0x00, 0x00));

    public object ConvertBack(object value, Type targetType, object parameter, string language)
        => throw new NotImplementedException();
}

public class BoolToForegroundConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, string language)
        => value is true
            ? new SolidColorBrush(Color.FromArgb(0xFF, 0x9B, 0x9B, 0x9B))
            : new SolidColorBrush(Color.FromArgb(0xFF, 0xD2, 0xD2, 0xD2));

    public object ConvertBack(object value, Type targetType, object parameter, string language)
        => throw new NotImplementedException();
}