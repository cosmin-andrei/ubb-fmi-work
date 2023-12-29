namespace sem11.domain;

public enum KnowledgeLevel
{
    Junior, Medium, Senior
}
    
public class Angajat: Entity<string>
{
    // private string nume;
    //
    // public string Nume
    // {
    //     get => nume;
    //     set => nume = value ?? throw new ArgumentNullException(nameof(value));
    // }
    public string Nume { get; set; }
    

    public double VenitPeOra { get; set; }

    public KnowledgeLevel Level { get; set; }

    public override string ToString()
    {
        return Id + " " + Nume + " " + this.Level + " " + this.VenitPeOra;
    }
        
}