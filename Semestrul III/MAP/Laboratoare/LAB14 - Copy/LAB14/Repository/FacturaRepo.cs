using LAB14.Domain;

namespace LAB14.Repository
{
    public class FacturaRepo : FileRepo<string, Factura>
    {
        private DocumentRepo docRepo;
        private AchizitieRepo achRepo;
        public FacturaRepo(string fileName, DocumentRepo docRepo, AchizitieRepo achRepo) : base(fileName)
        {
            this.docRepo = docRepo;
            this.achRepo = achRepo;
            ReadFromFile(fileName);
        }

        protected override Factura EntityFromString(string data)
        {
            string[] properties = data.Split(',');
            string id = properties[0];
            
            Document document = docRepo.FindOne(id);
            
            DateTime dataScadenta;
            EnumCategorie categorie = (EnumCategorie)Enum.Parse(typeof(EnumCategorie), properties[2]);
            DateTime.TryParseExact(properties[1], "d/M/yyyy", null,
                System.Globalization.DateTimeStyles.None, out dataScadenta);
            return new Factura(id, document.Nume, document.DataEmitere, dataScadenta, categorie);
        }
    }
}