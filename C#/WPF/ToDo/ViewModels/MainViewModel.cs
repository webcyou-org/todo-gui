using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows.Input;
using ToDo.Models;

namespace ToDo.ViewModels;

public class MainViewModel : INotifyPropertyChanged
{
    private readonly ObservableCollection<Todo> _todos;
    private TabFilter _activeTab = TabFilter.All;
    private string _inputText = "";
    private int _nextId = 5;

    public MainViewModel()
    {
        _todos = new ObservableCollection<Todo>
        {
            new() { Id = 1, Task = "Task 1", IsCompleted = false },
            new() { Id = 2, Task = "Task 2", IsCompleted = true },
            new() { Id = 3, Task = "Task 3", IsCompleted = false },
            new() { Id = 4, Task = "Task 4", IsCompleted = false },
        };

        foreach (var todo in _todos)
            todo.PropertyChanged += OnTodoPropertyChanged;

        AddTodoCommand = new RelayCommand(AddTodo, () => !string.IsNullOrWhiteSpace(_inputText));
        ToggleTodoCommand = new RelayCommand<int>(id => ToggleTodo(id));
        SetTabCommand = new RelayCommand<TabFilter>(tab => ActiveTab = tab);
    }

    public ICommand AddTodoCommand { get; }
    public ICommand ToggleTodoCommand { get; }
    public ICommand SetTabCommand { get; }

    public string InputText
    {
        get => _inputText;
        set
        {
            _inputText = value;
            Notify(nameof(InputText));
        }
    }

    public TabFilter ActiveTab
    {
        get => _activeTab;
        set
        {
            _activeTab = value;
            Notify(nameof(ActiveTab));
            Notify(nameof(FilteredTodos));
            Notify(nameof(IsAllActive));
            Notify(nameof(IsActiveTabActive));
            Notify(nameof(IsCompletedActive));
        }
    }

    public bool IsAllActive => _activeTab == TabFilter.All;
    public bool IsActiveTabActive => _activeTab == TabFilter.Active;
    public bool IsCompletedActive => _activeTab == TabFilter.Completed;

    public IEnumerable<Todo> FilteredTodos => _activeTab switch
    {
        TabFilter.Active => _todos.Where(t => !t.IsCompleted),
        TabFilter.Completed => _todos.Where(t => t.IsCompleted),
        _ => _todos,
    };

    private void AddTodo()
    {
        if (string.IsNullOrWhiteSpace(_inputText)) return;
        var todo = new Todo { Id = _nextId++, Task = _inputText.Trim(), IsCompleted = false };
        todo.PropertyChanged += OnTodoPropertyChanged;
        _todos.Add(todo);
        InputText = "";
        Notify(nameof(FilteredTodos));
    }

    private void ToggleTodo(int id)
    {
        var todo = _todos.FirstOrDefault(t => t.Id == id);
        if (todo is not null)
            todo.IsCompleted = !todo.IsCompleted;
    }

    private void OnTodoPropertyChanged(object? sender, PropertyChangedEventArgs e)
    {
        Notify(nameof(FilteredTodos));
    }

    public event PropertyChangedEventHandler? PropertyChanged;
    private void Notify(string name) =>
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
}