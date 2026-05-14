using CommunityToolkit.Mvvm.ComponentModel;

namespace ToDo.Models;

public partial class TodoItem : ObservableObject
{
    public int Id { get; init; }
    public string Task { get; init; } = "";

    [ObservableProperty]
    private bool _isCompleted;
}