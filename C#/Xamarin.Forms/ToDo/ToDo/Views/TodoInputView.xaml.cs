using System;
using ToDo.ViewModels;
using Xamarin.Forms;

namespace ToDo.Views
{
    public partial class TodoInputView : ContentView
    {
        public TodoInputView()
        {
            InitializeComponent();
        }

        private void OnEntryCompleted(object sender, EventArgs e)
        {
            if (BindingContext is MainViewModel vm)
                vm.AddTodoCommand.Execute(null);
        }
    }
}