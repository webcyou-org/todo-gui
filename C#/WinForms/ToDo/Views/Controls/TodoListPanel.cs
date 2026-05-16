using System.Drawing.Drawing2D;
using ToDo.Models;

namespace ToDo.Views.Controls;

/// <summary>
/// スクロール可能なTodoリスト。フィルタ変更時に Refresh() で再描画。
/// </summary>
public sealed class TodoListPanel : Panel
{
    private readonly Panel _inner;  // スクロール領域

    public event EventHandler<int>? CheckboxClicked;

    public TodoListPanel()
    {
        AutoScroll  = true;
        BackColor   = Theme.BG;

        _inner = new Panel { AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink };
        Controls.Add(_inner);
    }

    public void Refresh(IEnumerable<Todo> todos)
    {
        _inner.SuspendLayout();
        // 既存コントロールをクリア（Font等リソース解放）
        foreach (Control c in _inner.Controls) c.Dispose();
        _inner.Controls.Clear();

        int y = 0;
        foreach (var todo in todos)
        {
            var item = new TodoItemControl(todo)
            {
                Top   = y,
                Left  = 0,
                Width = ClientSize.Width,
            };
            item.CheckboxClicked += (_, id) => CheckboxClicked?.Invoke(this, id);
            _inner.Controls.Add(item);
            y += Theme.ItemH + Theme.ItemMb;
        }

        _inner.Height = y;
        _inner.ResumeLayout();
    }

    protected override void OnResize(EventArgs e)
    {
        base.OnResize(e);
        // アイテム幅をパネル幅に追従させる
        foreach (Control c in _inner.Controls)
            c.Width = ClientSize.Width;
    }
}

/// <summary>
/// 1件の Todo を描画するカスタムコントロール。
/// </summary>
internal sealed class TodoItemControl : Control
{
    private readonly Todo _todo;

    public event EventHandler<int>? CheckboxClicked;

    public TodoItemControl(Todo todo)
    {
        _todo  = todo;
        Height = Theme.ItemH;
        SetStyle(
            ControlStyles.UserPaint |
            ControlStyles.OptimizedDoubleBuffer |
            ControlStyles.AllPaintingInWmPaint, true);

        MouseClick += (_, e) =>
        {
            var cbRect = CheckboxRect();
            if (cbRect.Contains(e.Location))
                CheckboxClicked?.Invoke(this, _todo.Id);
        };
    }

    private Rectangle CheckboxRect()
    {
        int y = (Height - Theme.CbSize) / 2;
        return new Rectangle(Theme.ItemH / 2 - Theme.CbSize / 2, y, Theme.CbSize, Theme.CbSize);
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        var g = e.Graphics;
        g.SmoothingMode     = SmoothingMode.AntiAlias;
        g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;

        // ── Background ────────────────────────────────────────────────────────
        var bgRect = new Rectangle(0, 0, Width - 1, Height - 1);
        using var bgPath = MakeRoundPath(bgRect, Theme.Radius);
        using var bgBrush = new SolidBrush(Theme.Surface);
        g.FillPath(bgBrush, bgPath);

        // ── Checkbox ──────────────────────────────────────────────────────────
        var cb = CheckboxRect();
        if (_todo.IsCompleted)
        {
            using var fill = new SolidBrush(Theme.Accent);
            g.FillEllipse(fill, cb);
            // Checkmark
            using var pen = new Pen(Color.White, 1.5f) { LineJoin = LineJoin.Round };
            var cx = cb.X + cb.Width / 2f;
            var cy = cb.Y + cb.Height / 2f;
            var r  = cb.Width / 2f;
            g.DrawLines(pen, new[]
            {
                new PointF(cx - r * 0.45f, cy),
                new PointF(cx - r * 0.05f, cy + r * 0.45f),
                new PointF(cx + r * 0.50f, cy - r * 0.40f),
            });
        }
        else
        {
            using var pen = new Pen(Theme.CbBorder, 2f);
            g.DrawEllipse(pen, cb);
        }

        // ── Task text ─────────────────────────────────────────────────────────
        float textX = cb.Right + Theme.CbMr;
        float textW = Width - textX - Theme.PadY;

        var style = _todo.IsCompleted ? FontStyle.Strikeout : FontStyle.Regular;
        using var font  = Theme.MakeFont(Theme.FontNorm, style);
        using var brush = new SolidBrush(_todo.IsCompleted ? Theme.Muted : Theme.Text);

        var textRect = new RectangleF(textX, 0, textW, Height);
        var fmt = new StringFormat { LineAlignment = StringAlignment.Center, Trimming = StringTrimming.EllipsisCharacter };
        g.DrawString(_todo.Task, font, brush, textRect, fmt);
    }

    private static GraphicsPath MakeRoundPath(Rectangle r, int radius)
    {
        int d    = radius * 2;
        var path = new GraphicsPath();
        path.AddArc(r.X,         r.Y,          d, d, 180, 90);
        path.AddArc(r.Right - d, r.Y,          d, d, 270, 90);
        path.AddArc(r.Right - d, r.Bottom - d, d, d,   0, 90);
        path.AddArc(r.X,         r.Bottom - d, d, d,  90, 90);
        path.CloseFigure();
        return path;
    }
}
