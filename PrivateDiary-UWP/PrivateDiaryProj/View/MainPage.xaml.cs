using System;
using System.IO;
using System.Threading.Tasks;
using Windows.System;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Autofac;
using PrivateDiary.Model;
using PrivateDiary.Service;
using User = PrivateDiary.Model.User;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace PrivateDiary.View
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            CoreWindow.GetForCurrentThread().KeyDown += FormKeyDown;
        }

        private async void Registration(object sender, RoutedEventArgs e)
        {
            if (LoginTextBox.Text.Trim().Length == 0 || PasswordTextBox.Password.Trim().Length == 0)
            {
                await ShowErrorMessage("Login and password is required");
                return;
            }

            MainStack.Visibility = Visibility.Collapsed;
            ProgressRing.Visibility = Visibility.Visible;

            using (var scope = IoC.Container.BeginLifetimeScope())
            {
                var service = scope.Resolve<IUserService>();
                if (await service.Registration(LoginTextBox.Text, PasswordTextBox.Password))
                {
                    LoginUser();
                }
                else
                {
                    MainStack.Visibility = Visibility.Visible;
                    ProgressRing.Visibility = Visibility.Collapsed;
                    await ShowErrorMessage("Regiatration error");
                }
            }
        }

        private void Auth(object sender, RoutedEventArgs e)
        {
            LoginUser();
        }

        private async void LoginUser()
        {
            if (LoginTextBox.Text.Trim().Length == 0 || PasswordTextBox.Password.Trim().Length == 0)
            {
                await ShowErrorMessage("Login and password is required");
                return;
            }
            MainStack.Visibility = Visibility.Collapsed;
            ProgressRing.Visibility = Visibility.Visible;

            using (var scope = IoC.Container.BeginLifetimeScope())
            {
                var service = scope.Resolve<IUserService>();
                User user = await service.Auth(LoginTextBox.Text, PasswordTextBox.Password);

                MainStack.Visibility = Visibility.Visible;
                ProgressRing.Visibility = Visibility.Collapsed;

                if (user == null)
                {
                    await ShowErrorMessage("Login error");
                    return;
                }

                Constant.User = user;
                Constant.Key = PasswordTextBox.Password;
                var rootFrame = Window.Current.Content as Frame;
                rootFrame?.Navigate(typeof(Posts));
            }
        }
        

        private async Task<ContentDialogResult> ShowErrorMessage(string message, string title = "Error")
        {
            ContentDialog deleteFileDialog = new ContentDialog
            {
                Title = title,
                Content = message,
                PrimaryButtonText = "OK",
                SecondaryButtonText = "Cancel"
            };
            return await deleteFileDialog.ShowAsync();
        }

        private void FormKeyDown(CoreWindow sender, KeyEventArgs e)
        {
            if (e.VirtualKey == VirtualKey.Enter)
            {
                LoginUser();
            }
        }
    }
}
