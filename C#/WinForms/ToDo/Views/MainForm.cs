using ToDo.Models;
using ToDo.Views.Controls;

namespace ToDo.Views;

/// <summary>
/// MainForm — MVP の Presenter 役を兼ねる。
/// </summary>
public sealed class MainForm : Form
{
    // ── Model ─────────────────────────────────────────────────────────────────
    private readonly TodoModel _todoModel  = new();
    private readonly MenuModel _menuModel  = new();

    // ── View components ───────────────────────────────────────────────────────
    private readonly Label            _titleLabel;
    private readonly TodoInputControl _input;
    private readonly TabMenuControl   _tabs;
    private readonly TodoListPanel    _list;

    public MainForm()
    {
        // ── Window ────────────────────────────────────────────────────────────
        Text            = "ToDo";
        ClientSize      = new Size(800, 600);
        FormBorderStyle = FormBorderStyle.FixedSingle;
        MaximizeBox     = false;
        BackColor       = Theme.BG;
        AutoScaleMode   = AutoScaleMode.Dpi;

        // ── Title ─────────────────────────────────────────────────────────────
        _titleLabel = new Label
        {
            Text      = "ToDo",
            Font      = Theme.MakeFont(Theme.FontTitle, FontStyle.Bold),
            ForeColor = Theme.White,
            BackColor = Theme.BG,
            AutoSize  = true,
            Location  = new Point(Theme.PadX, Theme.PadY),
        };

        // ── Input ─────────────────────────────────────────────────────────────
        _input = new TodoInputControl
        {
            Left  = Theme.PadX,
            Width = ClientSize.Width - Theme.PadX * 2,
        };
        _input.TaskSubmitted += OnTaskSubmitted;

        // ── Tabs ──────────────────────────────────────────────────────────────
        _tabs = new TabMenuControl { Left = Theme.PadX };
        _tabs.TabChanged += OnTabChanged;

        // ── List ──────────────────────────────────────────────────────────────
        _list = new TodoListPanel
        {
            Left  = Theme.PadX,
            Width = ClientSize.Width - Theme.PadX * 2,
        };
        _list.CheckboxClicked += OnCheckboxClicked;

        Controls.AddRange([_titleLabel, _input, _tabs, _list]);
        Layout += (_, _) => DoLayout();
        DoLayout();
        RefreshList();
    }

    // ── Layout ────────────────────────────────────────────────────────────────

    private void DoLayout()
    {
        int x = Theme.PadX;
        int y = Theme.PadY;

        _titleLabel.Location = new Point(x, y);
        y += _titleLabel.PreferredHeight + Theme.TitleMb;

        _input.SetBounds(x, y, ClientSize.Width - x * 2, Theme.InputH);
        y += Theme.InputH + Theme.InputMb;

        _tabs.Location = new Point(x, y);
        y += _tabs.Height + Theme.TabMb;

        _list.SetBounds(x, y, ClientSize.Width - x * 2, ClientSize.Height - y - Theme.PadY);
    }

    // ── Event handlers ────────────────────────────────────────────────────────

    private void OnTaskSubmitted(object? s, string task)
    {
        _todoModel.AddTodo(task);
        RefreshList();
    }

    private void OnTabChanged(object? s, TabFilter tab)
    {
        _menuModel.SetActiveTab(tab);
        RefreshList();
    }

    private void OnCheckboxClicked(object? s, int id)
    {
        _todoModel.ToggleCompleted(id);
        RefreshList();
    }

    private void RefreshList() =>
        _list.Refresh(_todoModel.Filtered(_menuModel.ActiveTab));
}
