using Microsoft.UI.Text;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using ToDo.Models;
using ToDo.ViewModels;
using Windows.System;
using Windows.UI;

namespace ToDo;

public sealed partial class MainPage : Page
{
    private readonly MainViewModel _viewModel;

    private static readonly SolidColorBrush AccentBrush =
        new(Color.FromArgb(0xFF, 0x5D, 0xC2, 0xAF));
    private static readonly SolidColorBrush TransparentBrush =
        new(Color.FromArgb(0x00, 0x00, 0x00, 0x00));

    public MainPage()
    {
        this.InitializeComponent();
        _viewModel = new MainViewModel();
        this.DataContext = _viewModel;
    }

    // ── Input ────────────────────────────────────────────

    private void TaskInput_KeyDown(object sender, KeyRoutedEventArgs e)
    {
        if (e.Key == VirtualKey.Enter)
        {
            _viewModel.InputText = TaskInput.Text;
            _viewModel.AddTodo();
            TaskInput.Text = string.Empty;
        }
    }

    private void TaskInput_GotFocus(object sender, RoutedEventArgs e)
        => TaskInput.BorderBrush = AccentBrush;

    private void TaskInput_LostFocus(object sender, RoutedEventArgs e)
        => TaskInput.BorderBrush = TransparentBrush;

    // ── Tabs ─────────────────────────────────────────────

    private void AllTab_Tapped(object sender, TappedRoutedEventArgs e)
    {
        _viewModel.SetActiveTab(TabFilter.All);
        UpdateTabFontWeights(TabFilter.All);
    }

    private void ActiveTab_Tapped(object sender, TappedRoutedEventArgs e)
    {
        _viewModel.SetActiveTab(TabFilter.Active);
        UpdateTabFontWeights(TabFilter.Active);
    }

    private void CompletedTab_Tapped(object sender, TappedRoutedEventArgs e)
    {
        _viewModel.SetActiveTab(TabFilter.Completed);
        UpdateTabFontWeights(TabFilter.Completed);
    }

    private void UpdateTabFontWeights(TabFilter active)
    {
        AllTabText.FontWeight = active == TabFilter.All ? FontWeights.Bold : FontWeights.Normal;
        ActiveTabText.FontWeight = active == TabFilter.Active ? FontWeights.Bold : FontWeights.Normal;
        CompletedTabText.FontWeight = active == TabFilter.Completed ? FontWeights.Bold : FontWeights.Normal;
    }

    // ── Todo List ─────────────────────────────────────────

    private void Checkbox_Tapped(object sender, TappedRoutedEventArgs e)
    {
        if (sender is FrameworkElement element && element.DataContext is Todo todo)
        {
            _viewModel.ToggleCompleted(todo.Id);
            e.Handled = true;
        }
    }
}