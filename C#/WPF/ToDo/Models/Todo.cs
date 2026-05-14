using System.ComponentModel;

namespace ToDo.Models;

public class Todo : INotifyPropertyChanged
{
    private bool _isCompleted;

    public int Id { get; init; }
    public string Task { get; init; } = "";

    public bool IsCompleted
    {
        get => _isCompleted;
        set
        {
            if (_isCompleted == value) return;
            _isCompleted = value;
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(IsCompleted)));
        }
    }

    public event PropertyChangedEventHandler? PropertyChanged;
}