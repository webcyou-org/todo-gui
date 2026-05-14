using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using ToDo.Models;

namespace ToDo.ViewModels
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private readonly ObservableCollection<Todo> _allTodos;
        private string _activeTab = "All";
        private int _nextId = 5;

        public ObservableCollection<Todo> FilteredTodos { get; } = new ObservableCollection<Todo>();

        public bool IsAllActive => _activeTab == "All";
        public bool IsActiveActive => _activeTab == "Active";
        public bool IsCompletedActive => _activeTab == "Completed";

        public MainViewModel()
        {
            _allTodos = new ObservableCollection<Todo>
            {
                new Todo { Id = 1, Task = "Task 1", IsCompleted = false },
                new Todo { Id = 2, Task = "Task 2", IsCompleted = true },
                new Todo { Id = 3, Task = "Task 3", IsCompleted = false },
                new Todo { Id = 4, Task = "Task 4", IsCompleted = false },
            };
            RefreshFilteredTodos();
        }

        public void AddTodo(string task)
        {
            if (string.IsNullOrWhiteSpace(task)) return;
            _allTodos.Add(new Todo { Id = _nextId++, Task = task.Trim(), IsCompleted = false });
            RefreshFilteredTodos();
        }

        public void ToggleTodo(int id)
        {
            var todo = _allTodos.FirstOrDefault(t => t.Id == id);
            if (todo == null) return;
            todo.IsCompleted = !todo.IsCompleted;
            RefreshFilteredTodos();
        }

        public void SetActiveTab(string tab)
        {
            _activeTab = tab;
            OnPropertyChanged(nameof(IsAllActive));
            OnPropertyChanged(nameof(IsActiveActive));
            OnPropertyChanged(nameof(IsCompletedActive));
            RefreshFilteredTodos();
        }

        private void RefreshFilteredTodos()
        {
            FilteredTodos.Clear();
            IEnumerable<Todo> filtered;
            switch (_activeTab)
            {
                case "Active":
                    filtered = _allTodos.Where(t => !t.IsCompleted);
                    break;
                case "Completed":
                    filtered = _allTodos.Where(t => t.IsCompleted);
                    break;
                default:
                    filtered = _allTodos;
                    break;
            }
            foreach (var todo in filtered)
                FilteredTodos.Add(todo);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
            => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}