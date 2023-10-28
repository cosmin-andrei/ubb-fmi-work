package g221.map;

import java.util.Arrays;
import java.util.List;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {

    public static <E> void  printArie(List<E> l, Arie<E> f) {
        l.forEach(x-> System.out.println(f.compute(x)));
        l.forEach(System.out::println);
        //TODO: de cugetat la inlocuirea functiei lambda cu referinta la metoda


    }

    public static void main(String[] args) {

        Cerc cerc1 = new Cerc(2.0);
        Cerc cerc2 = new Cerc(3.0);
        List<Cerc> listaCercuri = Arrays.asList(cerc1, cerc2);

        Patrat patrat1 = new Patrat(1.0);
        Patrat patrat2 = new Patrat(2.0);
        List<Patrat> listaPatraturi = Arrays.asList(patrat1, patrat2);

        Arie<Cerc> arieCerc = (Cerc c) -> {
            return Math.PI*c.getRaza()* c.getRaza();
        };

        Arie<Patrat> ariePatrat = patrat -> patrat.getLatura() * patrat.getLatura();

//        Arie<Patrat> ariePatrat2 = new Arie<Patrat>(){
//
//            @Override
//            public Double compute(Patrat entity) {
//                return null;
//            }
//        }
        List<String> stringList4 = Arrays.asList("abc","abd","bcd","bce","cab");

        stringList4.stream()
                        .filter(str -> {
                            System.out.println(str);
                            return str.startsWith("b");
                        })
                                .map(str->{
                                    System.out.println(str);
                                    return str.toUpperCase();
                                })
                                        .forEach(System.out::println);

        //outputul secv de cod (asta era cerinta)
        //TODO: sa construiti un exemplu similar cu sorter

        System.out.println(arieCerc.compute(cerc1));
        System.out.println(arieCerc.compute(cerc2));
        System.out.println(ariePatrat.compute(patrat1));
        System.out.println(ariePatrat.compute(patrat2));

    }
}