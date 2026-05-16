using Xamarin.Forms;

namespace ToDo
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();
            MainPage = new Views.MainPage();
        }
    }
}