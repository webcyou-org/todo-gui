using System.Drawing.Drawing2D;

namespace ToDo.Views.Controls;

/// <summary>
/// 角丸テキストボックス。プレースホルダー・フォーカスボーダーを自前描画。
/// </summary>
public sealed class TodoInputControl : UserControl
{
    private readonly TextBox _box;
    private bool _isPlaceholder = true;
    private bool _focused;

    public event EventHandler<string>? TaskSubmitted;

    public TodoInputControl()
    {
        Height = Theme.InputH;
        BackColor = Theme.BG;   // 親背景色（角丸コーナー透過のため）

        SetStyle(
            ControlStyles.UserPaint |
            ControlStyles.OptimizedDoubleBuffer |
            ControlStyles.AllPaintingInWmPaint, true);

        _box = new TextBox
        {
            BorderStyle = BorderStyle.None,
            BackColor   = Theme.Input,
            ForeColor   = Theme.Muted,
            Font        = Theme.MakeFont(Theme.FontNorm),
            Text        = "Add Task",
        };

        _box.GotFocus += OnBoxGotFocus;
        _box.LostFocus += OnBoxLostFocus;
        _box.KeyDown  += OnBoxKeyDown;
        _box.TextChanged += (_, _) => { if (!_isPlaceholder) Invalidate(); };

        Controls.Add(_box);
        Resize += (_, _) => LayoutBox();
        LayoutBox();

        // 角丸でクリッピング
        UpdateRegion();
    }

    private void LayoutBox()
    {
        int py = Math.Max(0, (Height - _box.PreferredHeight) / 2);
        _box.SetBounds(Theme.PadX - Theme.PadY, py,
                       Width - (Theme.PadX - Theme.PadY) * 2, _box.PreferredHeight);
        UpdateRegion();
    }

    private void UpdateRegion()
    {
        var path = MakeRoundPath(new Rectangle(0, 0, Width, Height), Theme.Radius);
        Region = new Region(path);
    }

    private void OnBoxGotFocus(object? s, EventArgs e)
    {
        if (_isPlaceholder)
        {
            _box.Text      = "";
            _box.ForeColor = Theme.White;
            _isPlaceholder = false;
        }
        _focused = true;
        Invalidate();
    }

    private void OnBoxLostFocus(object? s, EventArgs e)
    {
        if (string.IsNullOrEmpty(_box.Text))
        {
            _box.Text      = "Add Task";
            _box.ForeColor = Theme.Muted;
            _isPlaceholder = true;
        }
        _focused = false;
        Invalidate();
    }

    private void OnBoxKeyDown(object? s, KeyEventArgs e)
    {
        if (e.KeyCode != Keys.Enter) return;
        e.Handled = e.SuppressKeyPress = true;

        if (_isPlaceholder || string.IsNullOrWhiteSpace(_box.Text)) return;
        TaskSubmitted?.Invoke(this, _box.Text.Trim());
        _box.Text      = "";
        _box.ForeColor = Theme.White;
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        var g = e.Graphics;
        g.SmoothingMode = SmoothingMode.AntiAlias;

        var rect = new Rectangle(0, 0, Width - 1, Height - 1);
        using var path = MakeRoundPath(rect, Theme.Radius);
        using var bg   = new SolidBrush(Theme.Input);
        g.FillPath(bg, path);

        if (_focused)
            using (var pen = new Pen(Theme.Accent, 1f))
                g.DrawPath(pen, path);
    }

    private static GraphicsPath MakeRoundPath(Rectangle r, int radius)
    {
        int d    = radius * 2;
        var path = new GraphicsPath();
        path.AddArc(r.X,          r.Y,           d, d, 180, 90);
        path.AddArc(r.Right - d,  r.Y,           d, d, 270, 90);
        path.AddArc(r.Right - d,  r.Bottom - d,  d, d,   0, 90);
        path.AddArc(r.X,          r.Bottom - d,  d, d,  90, 90);
        path.CloseFigure();
        return path;
    }
}
