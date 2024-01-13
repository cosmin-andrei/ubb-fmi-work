namespace LAB14.Domain;

public class Achizitie : Entity<string>
{
    public string Produs { get; set; }
    public int Cantitate { get; set; }
    public double PretProdus { get; set; }
    public Factura Bill { get; set; }

    public Achizitie(string id, string produs, int cantitate, double pretProdus, Factura bill) : base(id)
    {
        Produs = produs;
        Cantitate = cantitate;
        PretProdus = pretProdus;
        Bill = bill;
    }
}