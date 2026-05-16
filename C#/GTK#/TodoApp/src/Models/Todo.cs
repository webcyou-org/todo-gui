namespace TodoApp.Models;

public class Todo
{
    public int Id { get; set; }
    public string Task { get; set; } = string.Empty;
    public bool IsCompleted { get; set; }
}