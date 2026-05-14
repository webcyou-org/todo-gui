using Avalonia.Controls;
using ToDo.ViewModels;

namespace ToDo;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        DataContext = new MainViewModel();
    }
}