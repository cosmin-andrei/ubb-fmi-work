using LAB14.Domain;

namespace LAB14.Repository
{
    public abstract class FileRepo<Id,E> : InMemoryRepo<Id,E>
        where E : Entity<Id>
    {
        public FileRepo(string fileName)
        {
            // ReadFromFile(fileName);
        }

        public void ReadFromFile(string fileName)
        {
            try
            {
                StreamReader streamReader = new StreamReader(fileName);
                string data;
                while (true)
                {
                    data = streamReader.ReadLine();
                    if (data == null)
                        break;

                    Save(EntityFromString(data));
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine($"Error reading from file: {ex.Message}");
            }
            // catch (Exception ex)
            // {
            //     Console.WriteLine($"Unexpected error: {ex.Message}");
            // }
        }
        

        protected abstract E EntityFromString(string data);
    }
}