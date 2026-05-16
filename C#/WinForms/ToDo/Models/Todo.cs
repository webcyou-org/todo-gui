namespace ToDo.Models;

public class Todo
{
    public int    Id          { get; init; }
    public string Task        { get; set; } = "";
    public bool   IsCompleted { get; set; }
}
