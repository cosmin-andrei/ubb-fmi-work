using LAB14.Domain;

namespace LAB14.Repository
{
    public class AchizitieRepo : FileRepo<string, Achizitie>
    {
        private string fileBills;

        public AchizitieRepo(string fileName, string fileBills) : base(fileName)
        {
            ReadFromFile(fileName);
            this.fileBills = fileBills;
        }

        protected override Achizitie EntityFromString(string data)
        {
            string[] properties = data.Split(',');
            string id = properties[0];

            Factura factura = new Factura();
            factura.Id = properties[4];

            return new Achizitie(
                id,
                properties[1],
                int.Parse(properties[2]),
                double.Parse(properties[3]),
                factura
            );

        }
    }
}