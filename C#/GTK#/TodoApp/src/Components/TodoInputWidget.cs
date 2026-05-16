using Gtk;

namespace TodoApp.Components;

public class TodoInputWidget : Entry
{
    public event Action<string>? TaskSubmitted;

    public TodoInputWidget()
    {
        PlaceholderText = "Add Task";
        HasFrame        = false;
        HeightRequest   = 35;
        StyleContext.AddClass("todo-input");

        Activated += (_, _) =>
        {
            var text = Text.Trim();
            if (!string.IsNullOrEmpty(text))
            {
                TaskSubmitted?.Invoke(text);
                Text = string.Empty;
            }
        };
    }
}