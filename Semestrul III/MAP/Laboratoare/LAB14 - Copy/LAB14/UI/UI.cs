using LAB14.Domain;

namespace LAB14.UI
{
    public class Ui
    {
        private Service.Service _service;

        public Ui(Service.Service service)
        {
            this._service = service;
        }

        public void Run()
        {
            while (true)
            {
                Console.WriteLine("\nMeniu:");
                Console.WriteLine("0 - exit");
                Console.WriteLine("1 - Sa se afiseze toate documentele");
                Console.WriteLine("2 - Sa se afiseze toate facturile scadente in luna curenta");
                Console.WriteLine("3 - Sa se afiseze toate facturile cu cel putin 3 produse");
                Console.WriteLine("4 - Sa se afiseze achizitiile din categoria Utilities");
                Console.WriteLine("5 - Sa se afiseze categoria de facturi cu cele mai multe cheltuieli");
                Console.WriteLine("\n");

                Console.WriteLine("Introdu comanda: ");
                try
                {
                    int cmd = int.Parse(Console.ReadLine());
                    switch (cmd)
                    {
                        case 0:
                            return;
                        case 1:
                            foreach (Document document in _service.DocumentsByYear())
                            {
                                Console.WriteLine(document.Nume + " - " + document.DataEmitere);
                            }
                            break;
                        case 2:
                            foreach (Factura factura in _service.InvoicesByMonth())
                            {
                                Console.WriteLine(factura.Nume + " - " + factura.dataScadenta);
                            }
                            break;
                        case 3:
                            foreach (Factura factura in _service.InvoicesByCant())
                            {
                                Console.WriteLine(factura.Nume + " - " + _service.CountCant(factura.achizitii));
                            }
                            break;
                        case 4:
                            foreach (var ach in _service.AchizitiiByCategory())
                            {
                                Console.WriteLine(ach.Item1.Produs + " " + ach.Item2);
                            }
                            break;
                        case 5:
                            Console.WriteLine(_service.InvoicesByCheltuieli());
                            break;
                        default:
                            Console.WriteLine("Comandă invalidă");
                            break;
                    }
                }
                catch (FormatException)
                {
                    Console.WriteLine("Comandă invalidă. Introduceți un număr.");
                }
            }
        }
    }
}
