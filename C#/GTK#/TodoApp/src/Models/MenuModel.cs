namespace TodoApp.Models;

public class MenuModel
{
    private readonly List<TabMenu> _tabList = new()
    {
        new TabMenu { Text = "All",       Filter = TabFilter.All,       IsActive = true  },
        new TabMenu { Text = "Active",    Filter = TabFilter.Active,    IsActive = false },
        new TabMenu { Text = "Completed", Filter = TabFilter.Completed, IsActive = false },
    };

    public IReadOnlyList<TabMenu> GetTabList() => _tabList.AsReadOnly();

    public TabMenu GetActiveTab() => _tabList.First(t => t.IsActive);

    public void SetActiveTab(TabMenu item)
    {
        foreach (var t in _tabList) t.IsActive = false;
        item.IsActive = true;
    }
}