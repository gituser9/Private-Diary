using System;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace PrivateDiary.Main
{
    public static class RestClient
    {
        public static async Task<T> Get<T>(string url) where T : class 
        {
            var client = new HttpClient();
            var uri = new Uri(url);

            HttpResponseMessage response = await client.GetAsync(uri);
            string json = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<T>(json);
        }

        public static async Task<T> Post<T>(string url, object data) where T : class
        {
            var client = new HttpClient();
            var uri = new Uri(url);
            var stringContent = new StringContent(JsonConvert.SerializeObject(data), Encoding.UTF8, "application/json");
            HttpResponseMessage response = await client.PostAsync(uri, stringContent);
            string json = await response.Content.ReadAsStringAsync();

            return JsonConvert.DeserializeObject<T>(json);
        }
    }
}
