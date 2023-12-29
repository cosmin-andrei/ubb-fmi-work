using LAB14.Domain;
using LAB14.Repository;

namespace LAB14.Service;

public class Service
{
    private readonly IRepository<string, Achizitie> achizitieRepo;
    private readonly IRepository<string, Factura> facturaRepo;
    private readonly IRepository<string, Document> documentRepo;

    public Service(IRepository<string, Achizitie> achizitieRepo, IRepository<string, Factura> facturaRepo, IRepository<string, Document> documentRepo)
    {
        this.achizitieRepo = achizitieRepo;
        this.facturaRepo = facturaRepo;
        this.documentRepo = documentRepo;

        foreach (var achizitie in achizitieRepo.FindAll())
        {
            Factura f = new Factura();
            foreach (var factura in facturaRepo.FindAll())
            {
                if (factura.Id == achizitie.IdFactura)
                {
                    f = factura;
                    break;
                }
            }

            List<Achizitie> achizities = f.achizitii;
            achizities.Add(achizitie);
            
        }
        
    }

    public IEnumerable<Document> DocumentsByYear()
    {
        return documentRepo.FindAll().Where(d => d.DataEmitere.Year == 2023);
    }

    public IEnumerable<Factura> InvoicesByMonth()
    {
        return facturaRepo.FindAll().Where(f => f.dataScadenta.Month == DateTime.Now.Month);
    }

    public IEnumerable<Factura> InvoicesByCant()
    {
        return facturaRepo.FindAll().Where(factura => CountCant(factura.achizitii) >= 3);
    }

    public IEnumerable<(Achizitie, string)> AchizitiiByCategory()
    {
        EnumCategorie categorie = EnumCategorie.Utilities;
        List<(Achizitie, string)> achizities = new List<(Achizitie, string)>();
        foreach (var f in facturaRepo.FindAll())
        {
            if (f.categorie == categorie)
            {
                foreach (var ach in achizitieRepo.FindAll())
                {
                    if (ach.IdFactura == f.Id)
                    {
                        achizities.Add((ach, f.Nume));
                    }
                }
            }
        }

        return achizities;
    }


    public EnumCategorie InvoicesByCheltuieli()
    {
        Dictionary<EnumCategorie, double> count = new Dictionary<EnumCategorie, double>();
        foreach (var factura in facturaRepo.FindAll())
        {
            foreach (var achizitie in factura.achizitii)
            {
                if (count.ContainsKey(factura.categorie))
                {
                    count[factura.categorie] += achizitie.Cantitate * achizitie.PretProdus;
                }
                else
                {
                    count.Add(factura.categorie, achizitie.Cantitate * achizitie.PretProdus);
                }
            }
        }
        
        EnumCategorie category = count.OrderByDescending(kv => kv.Value).FirstOrDefault().Key;
        return category;
    }


    public int CountCant(List<Achizitie> achizitii)
    {
        int s = 0;
        foreach (Achizitie achizitie in achizitii)
        {
            s += achizitie.Cantitate;
        }

        return s;
    }
    
}