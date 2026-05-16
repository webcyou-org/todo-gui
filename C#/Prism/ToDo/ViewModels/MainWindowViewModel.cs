using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using Prism.Commands;
using Prism.Mvvm;
using ToDo.Models;

namespace ToDo.ViewModels;

public class MainWindowViewModel : BindableBase
{
    private readonly ObservableCollection<Todo> _todos;
    private TabFilter _activeTab = TabFilter.All;
    private string _inputText = "";
    private int _nextId = 5;

    public MainWindowViewModel()
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

        AddTodoCommand = new DelegateCommand(AddTodo, () => !string.IsNullOrWhiteSpace(_inputText));
        ToggleTodoCommand = new DelegateCommand<Todo?>(ToggleTodo);
        SetTabCommand = new DelegateCommand<TabFilter?>(tab => { if (tab.HasValue) ActiveTab = tab.Value; });
    }

    public DelegateCommand AddTodoCommand { get; }
    public DelegateCommand<Todo?> ToggleTodoCommand { get; }
    public DelegateCommand<TabFilter?> SetTabCommand { get; }

    public string InputText
    {
        get => _inputText;
        set
        {
            SetProperty(ref _inputText, value);
            AddTodoCommand.RaiseCanExecuteChanged();
        }
    }

    public TabFilter ActiveTab
    {
        get => _activeTab;
        set
        {
            SetProperty(ref _activeTab, value);
            RaisePropertyChanged(nameof(FilteredTodos));
            RaisePropertyChanged(nameof(IsAllActive));
            RaisePropertyChanged(nameof(IsActiveTabActive));
            RaisePropertyChanged(nameof(IsCompletedActive));
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
        RaisePropertyChanged(nameof(FilteredTodos));
    }

    private void ToggleTodo(Todo? todo)
    {
        if (todo is null) return;
        var t = _todos.FirstOrDefault(x => x.Id == todo.Id);
        if (t is not null) t.IsCompleted = !t.IsCompleted;
    }

    private void OnTodoPropertyChanged(object? sender, PropertyChangedEventArgs e)
    {
        RaisePropertyChanged(nameof(FilteredTodos));
    }
}