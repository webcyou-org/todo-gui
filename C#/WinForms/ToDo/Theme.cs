namespace ToDo;

internal static class Theme
{
    // Colors
    public static readonly Color BG       = ColorTranslator.FromHtml("#1C1C1C");
    public static readonly Color Surface  = ColorTranslator.FromHtml("#2A2A2A");
    public static readonly Color Input    = ColorTranslator.FromHtml("#303030");
    public static readonly Color Text     = ColorTranslator.FromHtml("#D2D2D2");
    public static readonly Color White    = Color.White;
    public static readonly Color Muted    = ColorTranslator.FromHtml("#9B9B9B");
    public static readonly Color Accent   = ColorTranslator.FromHtml("#5DC2AF");
    public static readonly Color CbBorder = ColorTranslator.FromHtml("#D9D9D9");

    // Spacing & sizes
    public const int PadX    = 24;
    public const int PadY    = 10;
    public const int InputH  = 35;
    public const int ItemH   = 35;
    public const int ItemMb  = 5;
    public const int CbSize  = 16;
    public const int CbMr    = 18;
    public const int TitleMb = 14;
    public const int InputMb = 14;
    public const int TabMb   = 3;
    public const int TabPx   = 8;
    public const int Radius  = 4;

    // Fonts
    public const float FontTitle = 18f;
    public const float FontNorm  = 14f;

    public static Font MakeFont(float size, FontStyle style = FontStyle.Regular) =>
        new("Segoe UI", size, style, GraphicsUnit.Point);
}
