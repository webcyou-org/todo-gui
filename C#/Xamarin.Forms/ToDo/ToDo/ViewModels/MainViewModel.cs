using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows.Input;
using ToDo.Models;

namespace ToDo.ViewModels
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private readonly ObservableCollection<TodoItem> _todos;
        private string _activeTab = "All";
        private string _inputText = "";
        private int _nextId = 5;

        public MainViewModel()
        {
            _todos = new ObservableCollection<TodoItem>
            {
                new TodoItem { Id = 1, Task = "Task 1", IsCompleted = false },
                new TodoItem { Id = 2, Task = "Task 2", IsCompleted = true },
                new TodoItem { Id = 3, Task = "Task 3", IsCompleted = false },
                new TodoItem { Id = 4, Task = "Task 4", IsCompleted = false },
            };

            foreach (var todo in _todos)
                todo.PropertyChanged += OnTodoPropertyChanged;

            AddTodoCommand = new RelayCommand(AddTodo);
            ToggleTodoCommand = new RelayCommand<int>(ToggleTodo);
            SetTabCommand = new RelayCommand<string>(SetTab);
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

        public string ActiveTab
        {
            get => _activeTab;
            private set
            {
                _activeTab = value;
                Notify(nameof(ActiveTab));
                Notify(nameof(FilteredTodos));
                Notify(nameof(IsAllActive));
                Notify(nameof(IsActiveTabActive));
                Notify(nameof(IsCompletedActive));
            }
        }

        public bool IsAllActive => _activeTab == "All";
        public bool IsActiveTabActive => _activeTab == "Active";
        public bool IsCompletedActive => _activeTab == "Completed";

        public IEnumerable<TodoItem> FilteredTodos
        {
            get
            {
                switch (_activeTab)
                {
                    case "Active":
                        return _todos.Where(t => !t.IsCompleted);
                    case "Completed":
                        return _todos.Where(t => t.IsCompleted);
                    default:
                        return _todos;
                }
            }
        }

        private void AddTodo()
        {
            var task = _inputText?.Trim();
            if (string.IsNullOrEmpty(task)) return;
            var todo = new TodoItem { Id = _nextId++, Task = task, IsCompleted = false };
            todo.PropertyChanged += OnTodoPropertyChanged;
            _todos.Add(todo);
            InputText = "";
            Notify(nameof(FilteredTodos));
        }

        private void ToggleTodo(int id)
        {
            var todo = _todos.FirstOrDefault(t => t.Id == id);
            if (todo != null)
                todo.IsCompleted = !todo.IsCompleted;
        }

        private void SetTab(string tab) => ActiveTab = tab;

        private void OnTodoPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(TodoItem.IsCompleted))
                Notify(nameof(FilteredTodos));
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void Notify(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}