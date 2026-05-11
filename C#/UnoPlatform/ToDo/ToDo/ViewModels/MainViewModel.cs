using System.Collections.ObjectModel;
using System.ComponentModel;
using ToDo.Models;

namespace ToDo.ViewModels;

public class MainViewModel : INotifyPropertyChanged
{
    private readonly ObservableCollection<Todo> _todos;
    private TabFilter _activeTab = TabFilter.All;
    private string _inputText = string.Empty;
    private int _nextId = 5;

    public event PropertyChangedEventHandler? PropertyChanged;

    public MainViewModel()
    {
        _todos = new ObservableCollection<Todo>
        {
            new() { Id = 1, Task = "Task 1", IsCompleted = false },
            new() { Id = 2, Task = "Task 2", IsCompleted = true },
            new() { Id = 3, Task = "Task 3", IsCompleted = false },
            new() { Id = 4, Task = "Task 4", IsCompleted = false }
        };
        FilteredTodos = new ObservableCollection<Todo>();

        foreach (var todo in _todos)
            todo.PropertyChanged += OnTodoPropertyChanged;

        RefreshFilteredTodos();
    }

    public string InputText
    {
        get => _inputText;
        set { _inputText = value; Notify(nameof(InputText)); }
    }

    public TabFilter ActiveTab
    {
        get => _activeTab;
        set
        {
            _activeTab = value;
            Notify(nameof(ActiveTab));
            RefreshFilteredTodos();
        }
    }

    public ObservableCollection<Todo> FilteredTodos { get; }

    public void AddTodo()
    {
        if (string.IsNullOrWhiteSpace(_inputText)) return;
        var todo = new Todo { Id = _nextId++, Task = _inputText.Trim(), IsCompleted = false };
        todo.PropertyChanged += OnTodoPropertyChanged;
        _todos.Add(todo);
        InputText = string.Empty;
        RefreshFilteredTodos();
    }

    public void ToggleCompleted(int id)
    {
        var todo = _todos.FirstOrDefault(t => t.Id == id);
        if (todo != null)
            todo.IsCompleted = !todo.IsCompleted;
    }

    public void SetActiveTab(TabFilter tab) => ActiveTab = tab;

    private void OnTodoPropertyChanged(object? sender, PropertyChangedEventArgs e)
    {
        if (e.PropertyName == nameof(Todo.IsCompleted))
            RefreshFilteredTodos();
    }

    private void RefreshFilteredTodos()
    {
        FilteredTodos.Clear();
        var filtered = _activeTab switch
        {
            TabFilter.Active => _todos.Where(t => !t.IsCompleted),
            TabFilter.Completed => _todos.Where(t => t.IsCompleted),
            _ => _todos.AsEnumerable()
        };
        foreach (var todo in filtered)
            FilteredTodos.Add(todo);
    }

    private void Notify(string p) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(p));
}