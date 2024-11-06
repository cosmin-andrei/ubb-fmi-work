// See https://aka.ms/new-console-template for more information


using System.Data.SqlClient;

class Program
{
    
    // Connection string
    static string connectionString = @"Server=DESKTOP-COR\SQLEXPRESS10;" +
                                     " Database=Organizatie; Integrated Security = true;" +
                                     " TrustServerCertificate=true;";


    static Task Main(string[] args)
    {
        // testarea conexiunii
        try
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                if (connection.State == System.Data.ConnectionState.Open)
                {
                    Log("Conexiunea a fost creata cu succes.");
                }
            }
        }
        catch (Exception ex)
        {
            Log($"Eroare la crearea conexiunii: {ex.Message}");
        }

        Task first_task = Task.Run(() => ExecProc("Donator_Donatie_Deadlock"));
        Task second_task = Task.Run(() => ExecProc("Donatie_Donator_Deadlock"));

        return Task.WhenAll(first_task, second_task);
    }

    private static async Task ExecProc(string procName)
    {
        int count = 0;
        bool success = false;

        while (!success && count < 3)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    Log("Conexiunea a fost deschisa.");
                    Log($"Executare procedura: {procName}.");
                    await connection.OpenAsync();
                    using (SqlCommand command = new SqlCommand(procName, connection))
                    {
                        command.CommandType = System.Data.CommandType.StoredProcedure;
                        await command.ExecuteNonQueryAsync();
                        success = true;
                        Log($"{procName} executata cu succes.");
                    }
                }
            }
            catch (SqlException ex) when (ex.Number == 1205) //Deadlock err no
            {
                count++;
                Log($"Eroare la executare: {procName}: {ex.Message}");

                if (count >= 5)
                {
                    Log($"Nu s-a putut executa {procName} dupa 5 incercari.");
                }
            }
            catch (Exception ex)
            {
                Log($"Eroare la executare: {procName}: {ex.Message}");
                break;
            }
        }
    }
    
    private static void Log(string message)
    {
        Console.WriteLine($"{DateTime.Now} - {message}");
    }
    
}
