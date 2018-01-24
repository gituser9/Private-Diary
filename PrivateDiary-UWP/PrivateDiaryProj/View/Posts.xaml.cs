using System;
using System.Collections.ObjectModel;
using System.Linq;
using Windows.ApplicationModel.DataTransfer;
using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Navigation;
using Autofac;
using PrivateDiary.Model;
using PrivateDiary.Service;
using System.IO;
using System.Threading.Tasks;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace PrivateDiary.View
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Posts : Page
    {
        public ObservableCollection<Post> PostList { get; private set; }

        private Post _currentPost;
        private readonly PostService _postService = new PostService();
        private readonly RichEditLibrary _library = new RichEditLibrary();

        public Posts()
        {
            this.InitializeComponent();
        }

        protected override async void OnNavigatedTo(NavigationEventArgs e)
        {
            
            var posts = await _postService.GetAll();
            PostList = new ObservableCollection<Post>(posts);
        }

        private async void ShowPost(object sender, SelectionChangedEventArgs e)
        {
            if (!(TitleList.SelectedValue is Post selectedPost))
            {
                return;
            }

            DropState();

            var dbPost = await _postService.Get(selectedPost.Id);
            _currentPost = selectedPost;
            _currentPost.Body = dbPost.Body;

            TextBoxTitle.Text = _currentPost.Title;
            Display.Document.SetText(TextSetOptions.FormatRtf, _currentPost.Body);

            BodyStackPanel.Visibility = Visibility.Visible;
            TextBoxTitle.Visibility = Visibility.Visible;

            if (TextBoxTitle.Text == Constant.DefaultTitle)
            {
                TextBoxTitle.Focus(FocusState.Programmatic);
                TextBoxTitle.SelectAll();
            }

            ClosePaneButton.Visibility = Visibility;
        }

        private void AddPost(object sender, RoutedEventArgs e)
        {
            Post newPost = _postService.AddPost(Constant.DefaultTitle, string.Empty);

            if (newPost == null)
            {
                return;
            }

            PostList.Add(newPost);
            TitleList.SelectedValue = PostList.Last();
            _currentPost = newPost;
        }

        private void DropState()
        {
            Bold.IsChecked = false;
            Italic.IsChecked = false;
            Underline.IsChecked = false;

            Left.IsChecked = false;
            Centre.IsChecked = false;
            Right.IsChecked = false;

            Size.SelectedValue = Size.Items[Constant.DefaultFonSizeIndex];
            Colour.SelectedValue = Colour.Items.First();
        }






        #region UI RichText

        private void Bold_Click(object sender, RoutedEventArgs e)
        {
            Bold.IsChecked = _library.Bold(ref Display);
        }

        private void Italic_Click(object sender, RoutedEventArgs e)
        {
            Italic.IsChecked = _library.Italic(ref Display);
        }

        private void Underline_Click(object sender, RoutedEventArgs e)
        {
            Underline.IsChecked = _library.Underline(ref Display);
        }

        private void Left_Click(object sender, RoutedEventArgs e)
        {
            Left.IsChecked = _library.Left(ref Display);
            Centre.IsChecked = false;
            Right.IsChecked = false;
        }

        private void Centre_Click(object sender, RoutedEventArgs e)
        {
            Left.IsChecked = false;
            Centre.IsChecked = _library.Centre(ref Display);
            Right.IsChecked = false;
        }

        private void Right_Click(object sender, RoutedEventArgs e)
        {
            Left.IsChecked = false;
            Centre.IsChecked = false;
            Right.IsChecked = _library.Right(ref Display);
        }

        private void Size_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            _library.Size(ref Display, ref Size);
        }

        private void Colour_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            _library.Colour(ref Display, ref Colour);
        }

        #endregion




        private async void Save_Click(object sender, RoutedEventArgs e)
        {
            if (_currentPost == null)
            {
                return;
            }
            if (string.IsNullOrEmpty(TextBoxTitle.Text))
            {
                var emptyTitle = new ContentDialog
                {
                    Title = "Title is required",
                    Content = "Enter title for your post.",
                    CloseButtonText = "Ok"
                };
                await emptyTitle.ShowAsync();
                return;
            }

            Display.Document.GetText(TextGetOptions.FormatRtf, out string body);
            _postService.Update(body, TextBoxTitle.Text, _currentPost.Id);

            if (_currentPost.Title != TextBoxTitle.Text)
            {
                _currentPost.Title = TextBoxTitle.Text;
            }
        }

        private void Grid_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            FrameworkElement senderElement = sender as FrameworkElement;
            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(senderElement);
            flyoutBase.ShowAt(senderElement);
        }

        private async void RemovePost(object sender, RoutedEventArgs e)
        {
            if (_currentPost == null)
            {
                return;
            }

            await _postService.Delete(_currentPost.Id);
            PostList.Remove(_currentPost);

            _currentPost = null;
        }

        private void ClosePane(object sender, RoutedEventArgs e)
        {
            SplitView.IsPaneOpen = false;
            OpenPaneButton.Visibility = Visibility.Visible;
        }

        private void OpenPane(object sender, RoutedEventArgs e)
        {
            SplitView.IsPaneOpen = true;
            OpenPaneButton.Visibility = Visibility.Collapsed;
        }

        private async void TitleList_OnDragItemsCompleted(ListViewBase sender, DragItemsCompletedEventArgs args)
        {
            if (!(args.Items.First() is Post post))
            {
                return;
            }

            var index = PostList.IndexOf(post);
            await _postService.UpdatePosition(post.Id, index);
        }

        private async void ShowEditProfile(object sender, RoutedEventArgs e)
        {
            PrepareProfileDialog();
            var answer = await ProfileDialog.ShowAsync();

            if (answer != ContentDialogResult.Primary)
            {
                return;
            }
            using (var scope = IoC.Container.BeginLifetimeScope())
            {
                SplitView.Visibility = Visibility.Collapsed;
                ProgressRing.Visibility = Visibility.Visible;
                var userService = scope.Resolve<IUserService>();
                var user = await userService.Update(TextBoxLogin.Text, Constant.Key, TextBoxPassword.Password, Constant.User);
                SplitView.Visibility = Visibility.Visible;
                ProgressRing.Visibility = Visibility.Collapsed;
            }
        }

        private void TextBoxConfirmPassword_OnPasswordChanged(object sender, RoutedEventArgs e)
        {
            if (TextBoxPassword.Password.Length == 0)
            {
                return;
            }
            ProfileDialog.IsPrimaryButtonEnabled = TextBoxPassword.Password == TextBoxConfirmPassword.Password;
        }

        private void PrepareProfileDialog()
        {
            ProfileDialog.IsPrimaryButtonEnabled = false;
            TextBoxPassword.Password = string.Empty;
            TextBoxConfirmPassword.Password = string.Empty;
            TextBoxLogin.Text = string.Empty;
        }

        private async void DownloadDatabase(object sender, RoutedEventArgs e)
        {
            var folderPicker = new Windows.Storage.Pickers.FolderPicker
            {
                SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.Desktop
            };
            folderPicker.FileTypeFilter.Add("*");

            Windows.Storage.StorageFolder folder = await folderPicker.PickSingleFolderAsync();

            if (folder == null)
            {
                return;
            }

            Windows.Storage.AccessCache.StorageApplicationPermissions.FutureAccessList.AddOrReplace("PickedFolderToken", folder);
            string dbFilePath = Path.Combine(Windows.Storage.ApplicationData.Current.LocalFolder.Path, Constant.DbName);


            await Task.Run(() => { File.Copy(dbFilePath, Path.Combine(folder.Path, Constant.DbName)); });
        }

        private async void UploadDatabase(object sender, RoutedEventArgs e)
        {
            var picker = new Windows.Storage.Pickers.FileOpenPicker
            {
                ViewMode = Windows.Storage.Pickers.PickerViewMode.List,
                SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.ComputerFolder
            };
            picker.FileTypeFilter.Add(".dbx");
            Windows.Storage.StorageFile file = await picker.PickSingleFileAsync();

            if (file == null)
            {
                return;
            }

            string localFolderPath = Windows.Storage.ApplicationData.Current.LocalFolder.Path;
            await Task.Run(() =>
            {
                File.Copy(file.Path, Path.Combine(localFolderPath, Constant.DbName), true);
            });
            var emptyTitle = new ContentDialog
            {
                Title = "Restart Application",
                Content = "Please restart application for use new database.",
                CloseButtonText = "Ok"
            };
            await emptyTitle.ShowAsync();


            _currentPost = null;
        }

    }
}
