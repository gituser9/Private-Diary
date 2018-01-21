using System.ComponentModel;
using System.Runtime.CompilerServices;
using PrivateDiary.Annotations;

namespace PrivateDiary.Model
{
    public sealed class Post : INotifyPropertyChanged
    {
        private string _title;


        public int Id { get; set; }

        public int UserId { get; set; }

        public string Title
        {
            get => _title;
            set
            {
                _title = value;
                OnPropertyChanged(nameof(Title));
            }
        }

        public string Body { get; set; }

        public long Date { get; set; }


        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
