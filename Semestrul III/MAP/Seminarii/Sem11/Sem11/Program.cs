// See https://aka.ms/new-console-template for more information

namespace Sem11;

class Base
{
    public virtual String Method()
    {
        return "base";
    }
}


class Derived:Base
{
//     public override String Method()
//     {
//         return "derived";
//     }

    public new string Method()
    {
        return "derived";
    }
    
}


internal class Program
{
    public static void Main(string[] args)
    {
        Base b = new Derived();
        Derived d = new Derived();

        Console.WriteLine(b.Method());
        Console.WriteLine(d.Method());
    }
}