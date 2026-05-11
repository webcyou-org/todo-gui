using System.ComponentModel;

namespace ToDo.Models;

public class Todo : INotifyPropertyChanged
{
    private int _id;
    private string _task = string.Empty;
    private bool _isCompleted;

    public int Id
    {
        get => _id;
        set { _id = value; Notify(nameof(Id)); }
    }

    public string Task
    {
        get => _task;
        set { _task = value; Notify(nameof(Task)); }
    }

    public bool IsCompleted
    {
        get => _isCompleted;
        set { _isCompleted = value; Notify(nameof(IsCompleted)); }
    }

    public event PropertyChangedEventHandler? PropertyChanged;
    private void Notify(string p) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(p));
}