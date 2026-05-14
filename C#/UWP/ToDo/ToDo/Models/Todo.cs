using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ToDo.Models
{
    public class Todo : INotifyPropertyChanged
    {
        private bool _isCompleted;

        public int Id { get; set; }
        public string Task { get; set; }

        public bool IsCompleted
        {
            get => _isCompleted;
            set
            {
                if (_isCompleted == value) return;
                _isCompleted = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
            => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}