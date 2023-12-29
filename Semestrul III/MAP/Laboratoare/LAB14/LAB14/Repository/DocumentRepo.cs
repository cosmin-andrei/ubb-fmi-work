using LAB14.Domain;

namespace LAB14.Repository
{
    public class DocumentRepo : FileRepo<string, Document>
    {
        public DocumentRepo(string fileName) : base(fileName)
        {
            ReadFromFile(fileName);
        }
        
        protected override Document EntityFromString(string data)
        {
            string[] properties = data.Split(',');
            string id = properties[0];
            string nume = properties[1];
            DateTime dataEmitere;
            DateTime.TryParseExact(properties[2], "d/M/yyyy", null, System.Globalization.DateTimeStyles.None,
                out dataEmitere);
            return new Document(id, nume, dataEmitere);
        }
    }
}