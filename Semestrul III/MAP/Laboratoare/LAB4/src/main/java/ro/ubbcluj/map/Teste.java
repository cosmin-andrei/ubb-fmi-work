//package ro.ubbcluj.map;
//import ro.ubbcluj.map.domain.Prietenie;
//import ro.ubbcluj.map.domain.Tuple;
//import ro.ubbcluj.map.domain.Utilizator;
//import ro.ubbcluj.map.domain.validators.PrietenieValidator;
//import ro.ubbcluj.map.domain.validators.UtilizatorValidator;
//import ro.ubbcluj.map.repository.memory.InMemoryRepository;
//import ro.ubbcluj.map.service.PrietenieService;
//import ro.ubbcluj.map.service.UtilizatorService;
//
//import java.sql.SQLException;
//
//public class Teste {
//
//    public void testeUser() throws SQLException {
//            Utilizator u1 = new Utilizator("u1FirstName", "u1LastName");
//            u1.setId(10L);
//            Utilizator u2 = new Utilizator("u2FirstName", "u2LastName");
//            u2.setId(12L);
//            Utilizator u3 = new Utilizator("u3FirstName", "u3LastName");
//            u3.setId(13L);
//
//            InMemoryRepository<Long, Utilizator> repo = new InMemoryRepository<>(new UtilizatorValidator());
//
//            UtilizatorService serv = new UtilizatorService(repo);
//            try {
//                serv.adaugaUtilizator(u1);
//            } catch (SQLException e) {
//                throw new RuntimeException(e);
//            }
//            serv.adaugaUtilizator(u2);
//            serv.adaugaUtilizator(u3);
//
//            if(serv.getAll().size() != 3){
//            System.out.println("Eroare la adaugare useri");
//        }
//
//        serv.stergeUtilizator(10L);
//        serv.stergeUtilizator(12L);
//        serv.stergeUtilizator(13L);
//
//        if(!serv.getAll().isEmpty()){
//            System.out.println("Eroare la stergere useri");
//        }
//
//    }
//
//    public void testePrietenie() throws SQLException {
//
//        Utilizator u1 = new Utilizator("u1FirstName", "u1LastName");
//        u1.setId(1L);
//        Utilizator u2 = new Utilizator("u2FirstName", "u2LastName");
//        u2.setId(2L);
//        Utilizator u3 = new Utilizator("u3FirstName", "u3LastName");
//        u3.setId(3L);
//
//        InMemoryRepository<Long, Utilizator> repo = new InMemoryRepository<>(new UtilizatorValidator());
//
//        UtilizatorService serv = new UtilizatorService(repo);
//        serv.adaugaUtilizator(u1);
//        serv.adaugaUtilizator(u2);
//        serv.adaugaUtilizator(u3);
//
//        InMemoryRepository<Tuple<Long, Long>, Prietenie> repoPrietenie = new InMemoryRepository<>(new PrietenieValidator());
//        PrietenieService prietenieService = new PrietenieService(repo, repoPrietenie);
//
//        Prietenie prietenie = new Prietenie();
//        Tuple<Long, Long> idPr = new Tuple<>(1L, 2L);
//        prietenie.setId(idPr);
//        prietenieService.adaugaPrietenie(prietenie);
//        boolean ok;
//        ok = prietenieService.verificaExistenta(idPr);
//        if(!ok)
//            System.out.println("Prietenie adaugare eroare");
//
//        prietenieService.stergePrietenie(prietenie.getId());
//        ok = prietenieService.verificaExistenta(idPr);
//        if(ok==true)
//            System.out.println("Prietenie stergere eroare");
//
//
//        Utilizator u4 = new Utilizator("u4FirstName", "u4LastName");
//        u4.setId(4L);
//        Utilizator u5 = new Utilizator("u5FirstName", "u5LastName");
//        u5.setId(5L);
//        Utilizator u6 = new Utilizator("u6FirstName", "u6LastName");
//        u6.setId(6L);
//        Utilizator u7 = new Utilizator("u7FirstName", "u7LastName");
//        u7.setId(7L);
//
//        serv.adaugaUtilizator(u4);
//        serv.adaugaUtilizator(u5);
//        serv.adaugaUtilizator(u6);
//        serv.adaugaUtilizator(u7);
//
//
//        Prietenie prietenie2 = new Prietenie();
//        prietenie2.setId(new Tuple<>(1L, 2L));
//        prietenieService.adaugaPrietenie(prietenie2);
//
//        Prietenie prietenie3 = new Prietenie();
//        prietenie3.setId(new Tuple<>(1L, 3L));
//        prietenieService.adaugaPrietenie(prietenie3);
//
//        Prietenie prietenie4 = new Prietenie();
//        prietenie4.setId(new Tuple<>(4L, 5L));
//        prietenieService.adaugaPrietenie(prietenie4);
//
//        Prietenie prietenie5 = new Prietenie();
//        prietenie5.setId(new Tuple<>(4L, 6L));
//        prietenieService.adaugaPrietenie(prietenie5);
//
//        int rez = prietenieService.numarComunitati();
//        if(rez!=3)
//            System.out.println("Eroare");
//
////        prietenieService.stergeUserPrieteni(1L);
////        int rez2 = prietenieService.numarComunitati();
////        if(rez2!=5)
////            System.out.println("Eroare");
//
//    }
//
//    public void execute() throws SQLException {
//       testeUser();
//       testePrietenie();
//    }
//
//
//}
