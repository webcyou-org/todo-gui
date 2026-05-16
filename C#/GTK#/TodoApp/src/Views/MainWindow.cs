using Gtk;
using TodoApp.Components;
using TodoApp.Models;

namespace TodoApp.Views;

public class MainWindow : Window
{
    private readonly TodoModel      _todoModel;
    private readonly MenuModel      _menuModel;
    private readonly TodoInputWidget _input;
    private readonly TabMenuWidget   _tabs;
    private readonly TodoListWidget  _list;

    public MainWindow(TodoModel todoModel, MenuModel menuModel) : base("ToDo")
    {
        _todoModel = todoModel;
        _menuModel = menuModel;

        SetDefaultSize(800, 600);
        Resizable = false;
        DeleteEvent += (_, args) => { Application.Quit(); args.RetVal = true; };

        var root = new Box(Orientation.Vertical, 0)
        {
            MarginTop    = 10,
            MarginBottom = 10,
            MarginStart  = 24,
            MarginEnd    = 24,
        };

        // Title
        var title = new Label("ToDo") { Xalign = 0 };
        title.StyleContext.AddClass("title-label");
        root.PackStart(title, false, false, 0);
        root.PackStart(Spacer(14), false, false, 0);

        // Input
        _input = new TodoInputWidget();
        _input.TaskSubmitted += task =>
        {
            _todoModel.AddTodo(task);
            Refresh();
        };
        root.PackStart(_input, false, false, 0);
        root.PackStart(Spacer(14), false, false, 0);

        // Tabs
        _tabs = new TabMenuWidget();
        _tabs.TabSelected += tab =>
        {
            _menuModel.SetActiveTab(tab);
            Refresh();
        };
        root.PackStart(_tabs, false, false, 3);

        // Todo list
        _list = new TodoListWidget();
        _list.TodoToggled += id =>
        {
            _todoModel.ChangeCompleted(id);
            Refresh();
        };
        root.PackStart(_list, true, true, 0);

        Add(root);
        Refresh();
        ShowAll();
    }

    private void Refresh()
    {
        _tabs.Rebuild(_menuModel.GetTabList());
        _list.Rebuild(_todoModel.GetFilteredTodos(_menuModel.GetActiveTab().Filter));
    }

    private static Label Spacer(int height) => new("") { HeightRequest = height };
}