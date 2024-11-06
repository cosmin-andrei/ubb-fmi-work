using System;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;


namespace CSharpRestClient
{
	class MainClass
	{
		//static HttpClient client = new HttpClient();
		//pentru jurnalizarea operatiilor efectuate si a datelor trimise/primite
		static HttpClient client = new HttpClient(new LoggingHandler(new HttpClientHandler()));

		private static string URL_Base = "http://localhost:8080/chat/users";

		public static void Main(string[] args)
		{
			//Console.WriteLine("Hello World!");
			RunAsync().Wait();
		}


		static async Task RunAsync()
		{
			client.BaseAddress = new Uri("http://localhost:8080/chat/greeting");
			client.DefaultRequestHeaders.Accept.Clear();
			//client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("text/plain"));
			client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
			// Get the string
			//String text = await GetTextAsync("http://localhost:8080/chat/users/greeting");
			//Console.WriteLine("am obtinut {0}", text);
			//Get one user
			String username = "ana";
			Console.WriteLine("Get user {0}", username);
			User result1 = await GetUserAsync("http://localhost:8080/chat/users/"+username);
			Console.WriteLine("Am primit {0}", result1);
			
			
			//Create a user
			User  user = new  User{Id="test_2024",Name = "Test C#", Passwd = "test"};
			Console.WriteLine("Create user {0}", user);
			User result = await CreateUserAsync("http://localhost:8080/chat/users", user);
			Console.WriteLine("Am primit {0}", result);
			Console.ReadLine();
		}

		static async Task<String> GetTextAsync(string path)
		{
			String product = null;
			HttpResponseMessage response = await client.GetAsync(path);
			if (response.IsSuccessStatusCode)
			{
				product = await response.Content.ReadAsStringAsync();
			}
			return product;
		}
		static async Task<User> GetUserAsync(string path)
		{
			User product = null;
			HttpResponseMessage response = await client.GetAsync(path);
			if (response.IsSuccessStatusCode)
			{
				product = await response.Content.ReadAsAsync<User>();
			}
			return product;
		}

		
		static async Task<User> CreateUserAsync(string path, User user)
		{
			User result = null;
			HttpResponseMessage response = await client.PostAsJsonAsync(path, user);
			if (response.IsSuccessStatusCode)
			{
				result = await response.Content.ReadAsAsync<User>();
			}
			return result;
		}
	}
	public class User
	{
		[JsonProperty("passwd")]
		public string Passwd { get; set; }
		[JsonProperty("id")]
		public string Id { get; set; }
		[JsonProperty("name")]
		public string Name { get; set; }
		public User[] Friends { get; set; } 

		public override string ToString()
		{
			return string.Format("[User: Passwd={0}, Id={1}, Name={2}, Friends={3}]", Passwd, Id, Name, Friends);
		}
	}
	
	public class LoggingHandler : DelegatingHandler
    {
        public LoggingHandler(HttpMessageHandler innerHandler)
            : base(innerHandler)
        {
        }
    
        protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
        {
            Console.WriteLine("Request:");
            Console.WriteLine(request.ToString());
            if (request.Content != null)
            {
                Console.WriteLine(await request.Content.ReadAsStringAsync());
            }
            Console.WriteLine();
    
            HttpResponseMessage response = await base.SendAsync(request, cancellationToken);
    
            Console.WriteLine("Response:");
            Console.WriteLine(response.ToString());
            if (response.Content != null)
            {
                Console.WriteLine(await response.Content.ReadAsStringAsync());
            }
            Console.WriteLine();
    
            return response;
        }
    }
	
}
