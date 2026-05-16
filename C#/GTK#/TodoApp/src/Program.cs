using Gtk;
using TodoApp;
using TodoApp.Models;
using TodoApp.Views;

Application.Init();

var cssProvider = new CssProvider();
cssProvider.LoadFromData(Theme.Css);
StyleContext.AddProviderForScreen(
    Gdk.Screen.Default,
    cssProvider,
    StyleProviderPriority.Application);

var todoModel = new TodoModel();
var menuModel = new MenuModel();
var win       = new MainWindow(todoModel, menuModel);
win.Show();

Application.Run();