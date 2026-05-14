using System;
using System.Globalization;
using Avalonia.Data.Converters;
using Avalonia.Media;

namespace ToDo.Converters;

public class BoolToTextDecorationsConverter : IValueConverter
{
    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
        => value is true ? TextDecorations.Strikethrough : null;

    public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
        => throw new NotSupportedException();
}