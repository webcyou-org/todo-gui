using ToDo.Models;

namespace ToDo.Views.Controls;

/// <summary>
/// All / Active / Completed タブ。アクティブタブは Bold。
/// </summary>
public sealed class TabMenuControl : FlowLayoutPanel
{
    private static readonly TabFilter[] Filters =
        [TabFilter.All, TabFilter.Active, TabFilter.Completed];

    private readonly Label[] _labels = new Label[3];
    private TabFilter _active = TabFilter.All;

    public event EventHandler<TabFilter>? TabChanged;

    public TabMenuControl()
    {
        AutoSize      = true;
        FlowDirection = FlowDirection.LeftToRight;
        BackColor     = Theme.BG;
        WrapContents  = false;

        string[] names = ["All", "Active", "Completed"];

        for (int i = 0; i < 3; i++)
        {
            int idx = i;
            _labels[i] = new Label
            {
                Text        = names[i],
                AutoSize    = false,
                Height      = Theme.TabH,
                BackColor   = Theme.BG,
                ForeColor   = Theme.Text,
                TextAlign   = ContentAlignment.MiddleCenter,
                Cursor      = Cursors.Hand,
                Padding     = new Padding(Theme.TabPx, 0, Theme.TabPx, 0),
                MinimumSize = new Size(TextRenderer.MeasureText(
                    names[i],
                    Theme.MakeFont(Theme.FontNorm, FontStyle.Bold)).Width + Theme.TabPx * 2, 0),
            };
            _labels[i].Click += (_, _) => SetActive(Filters[idx]);
            Controls.Add(_labels[i]);
        }

        RefreshFonts();
    }

    private void SetActive(TabFilter tab)
    {
        _active = tab;
        RefreshFonts();
        TabChanged?.Invoke(this, tab);
    }

    private void RefreshFonts()
    {
        for (int i = 0; i < _labels.Length; i++)
            _labels[i].Font = Theme.MakeFont(Theme.FontNorm,
                Filters[i] == _active ? FontStyle.Bold : FontStyle.Regular);
    }
}
