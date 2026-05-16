using Gtk;
using TodoApp.Models;

namespace TodoApp.Components;

public class TabMenuWidget : Box
{
    public event Action<TabMenu>? TabSelected;

    public TabMenuWidget() : base(Orientation.Horizontal, 0) { }

    public void Rebuild(IReadOnlyList<TabMenu> tabs)
    {
        foreach (var child in Children) Remove(child);

        foreach (var tab in tabs)
        {
            var localTab = tab;
            var btn = new Button(tab.Text) { Relief = ReliefStyle.None };
            btn.StyleContext.AddClass("tab-btn");
            if (tab.IsActive) btn.StyleContext.AddClass("active");
            btn.Clicked += (_, _) => TabSelected?.Invoke(localTab);
            PackStart(btn, false, false, 0);
        }

        ShowAll();
    }
}