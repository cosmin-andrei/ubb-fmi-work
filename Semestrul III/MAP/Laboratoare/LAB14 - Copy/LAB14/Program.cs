using LAB14.Repository;
using LAB14.UI;

namespace LAB14;

public class Program
{
    static void Main()
    {
        DocumentRepo documentRepo = new DocumentRepo("documente.txt");
        AchizitieRepo achizitieRepo = new AchizitieRepo("achizitii.txt", "documente.txt");
        FacturaRepo facturaRepo = new FacturaRepo("facturi.txt", documentRepo, achizitieRepo);

        Service.Service service = new Service.Service(achizitieRepo, facturaRepo, documentRepo);
        
        Ui console = new Ui(service);
        console.Run();
    }
}