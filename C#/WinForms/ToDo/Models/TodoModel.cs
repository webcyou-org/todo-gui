namespace ToDo.Models;

public enum TabFilter { All, Active, Completed }

public class TodoModel
{
    private readonly List<Todo> _todos = new();
    private int _nextId = 1;

    public TodoModel()
    {
        AddSample("Task 1", false);
        AddSample("Task 2", true);
        AddSample("Task 3", false);
        AddSample("Task 4", false);
    }

    public void AddTodo(string task)
    {
        if (string.IsNullOrWhiteSpace(task)) return;
        _todos.Add(new Todo { Id = _nextId++, Task = task.Trim() });
    }

    public void ToggleCompleted(int id)
    {
        var t = _todos.FirstOrDefault(t => t.Id == id);
        if (t is not null) t.IsCompleted = !t.IsCompleted;
    }

    public void Remove(int id) => _todos.RemoveAll(t => t.Id == id);

    public IEnumerable<Todo> Filtered(TabFilter filter) => filter switch
    {
        TabFilter.Active    => _todos.Where(t => !t.IsCompleted),
        TabFilter.Completed => _todos.Where(t =>  t.IsCompleted),
        _                   => _todos,
    };

    private void AddSample(string task, bool done) =>
        _todos.Add(new Todo { Id = _nextId++, Task = task, IsCompleted = done });
}

public class MenuModel
{
    public TabFilter ActiveTab { get; private set; } = TabFilter.All;
    public void SetActiveTab(TabFilter tab) => ActiveTab = tab;
}
