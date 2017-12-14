using System;
using Windows.UI.Xaml.Data;
using PrivateDiary.Model;

namespace PrivateDiary.View.Converter
{
    public class DateFormatConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            if (value == null)
                return null;

            long timestamp = long.Parse(value.ToString());
            DateTime dateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0);
            dateTime = dateTime.AddSeconds(timestamp);

            return dateTime.ToString(Constant.DateFormat);
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}
