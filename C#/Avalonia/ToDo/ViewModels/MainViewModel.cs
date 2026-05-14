using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using ToDo.Models;

namespace ToDo.ViewModels;

public partial class MainViewModel : ObservableObject
{
    private readonly ObservableCollection<TodoItem> _allTodos = [];
    private int _nextId = 1;

    [ObservableProperty]
    private string _inputText = "";

    [ObservableProperty]
    private ObservableCollection<TodoItem> _filteredTodos = [];

    [ObservableProperty]
    private string _activeTab = "All";

    public MainViewModel()
    {
        AddItem(new TodoItem { Id = _nextId++, Task = "Task 1", IsCompleted = false });
        AddItem(new TodoItem { Id = _nextId++, Task = "Task 2", IsCompleted = true });
        AddItem(new TodoItem { Id = _nextId++, Task = "Task 3", IsCompleted = false });
        AddItem(new TodoItem { Id = _nextId++, Task = "Task 4", IsCompleted = false });
        UpdateFilteredTodos();
    }

    private void AddItem(TodoItem todo)
    {
        todo.PropertyChanged += OnTodoPropertyChanged;
        _allTodos.Add(todo);
    }

    private void OnTodoPropertyChanged(object? sender, PropertyChangedEventArgs e)
    {
        if (e.PropertyName == nameof(TodoItem.IsCompleted))
            UpdateFilteredTodos();
    }

    partial void OnActiveTabChanged(string value) => UpdateFilteredTodos();

    [RelayCommand]
    private void AddTodo()
    {
        var task = InputText.Trim();
        if (string.IsNullOrEmpty(task)) return;
        var todo = new TodoItem { Id = _nextId++, Task = task, IsCompleted = false };
        AddItem(todo);
        InputText = "";
        UpdateFilteredTodos();
    }

    [RelayCommand]
    private void SetActiveTab(string tab) => ActiveTab = tab;

    private void UpdateFilteredTodos()
    {
        var filtered = ActiveTab switch
        {
            "Active" => _allTodos.Where(t => !t.IsCompleted),
            "Completed" => _allTodos.Where(t => t.IsCompleted),
            _ => _allTodos.AsEnumerable()
        };
        FilteredTodos = new ObservableCollection<TodoItem>(filtered);
    }
}