using Gtk;
using TodoApp.Models;

namespace TodoApp.Components;

public class TodoListWidget : ScrolledWindow
{
    private readonly Box _innerBox;

    public event Action<int>? TodoToggled;

    public TodoListWidget() : base()
    {
        HscrollbarPolicy = PolicyType.Never;
        VscrollbarPolicy = PolicyType.Automatic;

        _innerBox = new Box(Orientation.Vertical, 5);
        Add(_innerBox);
    }

    public void Rebuild(IReadOnlyList<Todo> todos)
    {
        foreach (var child in _innerBox.Children) _innerBox.Remove(child);

        foreach (var todo in todos)
        {
            var localTodo = todo;
            var row = BuildTodoItem(todo);
            _innerBox.PackStart(row, false, false, 0);
            _ = localTodo; // suppress unused warning
        }

        _innerBox.ShowAll();
    }

    private Widget BuildTodoItem(Todo todo)
    {
        var row = new Box(Orientation.Horizontal, 0);
        row.StyleContext.AddClass("todo-item");
        row.HeightRequest = 35;

        // Circular checkbox — SizeRequest + Valign.Center prevent vertical stretching
        var cbBtn = new Button();
        cbBtn.StyleContext.AddClass("checkbox-circle");
        if (todo.IsCompleted) cbBtn.StyleContext.AddClass("checked");
        cbBtn.SetSizeRequest(16, 16);
        cbBtn.Valign = Align.Center;
        cbBtn.Halign = Align.Center;

        var id = todo.Id;
        cbBtn.Clicked += (_, _) => TodoToggled?.Invoke(id);

        // Spacer between checkbox and text
        var spacer = new Label("") { WidthRequest = 18 };
        spacer.Valign = Align.Center;

        // Task label
        var lbl = new Label(todo.Task) { Xalign = 0 };
        lbl.StyleContext.AddClass("todo-item-text");
        lbl.Valign = Align.Center;
        if (todo.IsCompleted) lbl.StyleContext.AddClass("completed");

        row.PackStart(cbBtn,   false, false, 0);
        row.PackStart(spacer,  false, false, 0);
        row.PackStart(lbl,     true,  true,  0);

        return row;
    }
}