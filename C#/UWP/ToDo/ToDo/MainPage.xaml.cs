using ToDo.Models;
using ToDo.ViewModels;
using Windows.System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace ToDo
{
    public sealed partial class MainPage : Page
    {
        private MainViewModel ViewModel => DataContext as MainViewModel;

        public MainPage()
        {
            this.InitializeComponent();
            this.DataContext = new MainViewModel();
        }

        private void TaskInput_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key != VirtualKey.Enter) return;
            ViewModel?.AddTodo(TaskInput.Text);
            TaskInput.Text = string.Empty;
            e.Handled = true;
        }

        private void AllTab_Click(object sender, RoutedEventArgs e)
            => ViewModel?.SetActiveTab("All");

        private void ActiveTab_Click(object sender, RoutedEventArgs e)
            => ViewModel?.SetActiveTab("Active");

        private void CompletedTab_Click(object sender, RoutedEventArgs e)
            => ViewModel?.SetActiveTab("Completed");

        // The DataContext inside the DataTemplate is the Todo item itself.
        private void Checkbox_Click(object sender, RoutedEventArgs e)
        {
            if (sender is FrameworkElement fe && fe.DataContext is Todo todo)
                ViewModel?.ToggleTodo(todo.Id);
        }
    }
}