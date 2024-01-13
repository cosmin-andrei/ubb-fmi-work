namespace LAB14.Domain;

public class Factura : Document
{
    public DateTime dataScadenta { get; set; }
    public List<Achizitie> achizitii { get; set; }
    public EnumCategorie categorie { get; set; }

    public Factura() { }
    public Factura(string id, string nume, DateTime dataEmitere, DateTime dataScadenta, EnumCategorie categorie)
        : base(id, nume, dataEmitere)
    {
        this.dataScadenta = dataScadenta;
        this.categorie = categorie;
        this.achizitii = new List<Achizitie>();
    }
}