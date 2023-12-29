using sem11.domain;

namespace sem11.repository;

public abstract class FileRepository<TID, TE>: InMemoryRepository<TID, TE> where TE: Entity<TID>
{
    private string fileName;

    protected FileRepository(string fileName)
    {
        this.fileName = fileName;
        readAll();
    }

    protected abstract string toLine(TE elem);
        
    protected abstract TE fromLine(String line);

    private void readAll()
    {
        using (StreamReader sr = new StreamReader(fileName))
        {
            string s;
            while ((s = sr.ReadLine()) != null)
            {
                TE entity= fromLine(s);
                Save(entity);
            }
        }
    }
}