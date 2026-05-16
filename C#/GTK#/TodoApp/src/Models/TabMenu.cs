namespace TodoApp.Models;

public enum TabFilter { All, Active, Completed }

public class TabMenu
{
    public string Text { get; set; } = string.Empty;
    public TabFilter Filter { get; set; }
    public bool IsActive { get; set; }
}