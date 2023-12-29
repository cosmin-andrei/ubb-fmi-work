using LAB14.Domain;

namespace LAB14.Repository
{
    public class AchizitieRepo : FileRepo<string, Achizitie>
    {
        public AchizitieRepo(string fileName) : base(fileName)
        {
            ReadFromFile(fileName);
        }

        protected override Achizitie EntityFromString(string data)
        {
            string[] properties = data.Split(',');
            string id = properties[0];

            return new Achizitie(
                id,
                properties[1],
                int.Parse(properties[2]),
                double.Parse(properties[3]),
                properties[4]
            );
        }
    }
}