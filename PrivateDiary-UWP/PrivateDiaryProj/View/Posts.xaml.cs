﻿using System;
using System.Collections.ObjectModel;
using System.Linq;
using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Input;
using PrivateDiary.Model;
using PrivateDiary.Service;

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

            PostList = new ObservableCollection<Post>(_postService.GetAll()); 
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

        /*private void New_Click(object sender, RoutedEventArgs e)
        {
            Library.New(Display);
        }

        private void Open_Click(object sender, RoutedEventArgs e)
        {
            Library.Open(Display);
        }*/

        #endregion




        private async void Save_Click(object sender, RoutedEventArgs e)
        {
            if (_currentPost == null)
            {
                return;
            }
            if (string.IsNullOrEmpty(TextBoxTitle.Text))
            {
                ContentDialog emptyTitle = new ContentDialog
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
            _currentPost.Title = TextBoxTitle.Text;
        }

        private void Grid_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            FrameworkElement senderElement = sender as FrameworkElement;
            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(senderElement);
            flyoutBase.ShowAt(senderElement);
        }

        private async void RemovePost(object sender, RoutedEventArgs e)
        {
            object datacontext = (e.OriginalSource as FrameworkElement)?.DataContext;

            if (datacontext == null)
            {
                return;
            }
            if (!(datacontext is Post post))
            {
                return;
            }

            await _postService.Delete(post.Id);
            PostList.Remove(post);
        }
    }
}