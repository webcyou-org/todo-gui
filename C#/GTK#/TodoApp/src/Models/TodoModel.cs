namespace TodoApp.Models;

public class TodoModel
{
    private readonly List<Todo> _list = new();
    private int _nextId = 1;

    public TodoModel()
    {
        _list.Add(new Todo { Id = _nextId++, Task = "Task 1", IsCompleted = false });
        _list.Add(new Todo { Id = _nextId++, Task = "Task 2", IsCompleted = true });
        _list.Add(new Todo { Id = _nextId++, Task = "Task 3", IsCompleted = false });
        _list.Add(new Todo { Id = _nextId++, Task = "Task 4", IsCompleted = false });
    }

    public IReadOnlyList<Todo> GetData() => _list.AsReadOnly();

    public void AddTodo(string task)
    {
        if (string.IsNullOrWhiteSpace(task)) return;
        _list.Add(new Todo { Id = _nextId++, Task = task.Trim(), IsCompleted = false });
    }

    public Todo? FindById(int id) => _list.FirstOrDefault(t => t.Id == id);

    public void ChangeCompleted(int id)
    {
        var todo = FindById(id);
        if (todo != null) todo.IsCompleted = !todo.IsCompleted;
    }

    public IReadOnlyList<Todo> GetFilteredTodos(TabFilter filter) => filter switch
    {
        TabFilter.Active    => _list.Where(t => !t.IsCompleted).ToList().AsReadOnly(),
        TabFilter.Completed => _list.Where(t =>  t.IsCompleted).ToList().AsReadOnly(),
        _                   => _list.AsReadOnly(),
    };

    public void RemoveData(int id) => _list.RemoveAll(t => t.Id == id);
}