using System;
using System.Globalization;
using Avalonia.Data.Converters;
using Avalonia.Media;

namespace ToDo.Converters;

public class TabFontWeightConverter : IValueConverter
{
    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
        => value?.ToString() == parameter?.ToString() ? FontWeight.Bold : FontWeight.Regular;

    public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
        => throw new NotSupportedException();
}