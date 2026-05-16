using System.ComponentModel;

namespace ToDo.Models
{
    public class TodoItem : INotifyPropertyChanged
    {
        private bool _isCompleted;

        public int Id { get; set; }
        public string Task { get; set; } = "";

        public bool IsCompleted
        {
            get => _isCompleted;
            set
            {
                if (_isCompleted != value)
                {
                    _isCompleted = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(IsCompleted)));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }
}