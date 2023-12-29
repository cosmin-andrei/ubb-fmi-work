namespace LAB14.Domain;

public class Document : Entity<string>
{
    public string Nume { get; set; }
    public DateTime DataEmitere { get; set; }

    
    public Document(){ }
    
    public Document(string id, string nume, DateTime dataEmitere) : base(id)
    {
        Nume = nume;
        DataEmitere = dataEmitere;
    }
}