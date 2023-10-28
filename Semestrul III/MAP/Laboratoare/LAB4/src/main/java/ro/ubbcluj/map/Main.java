package ro.ubbcluj.map;

import ro.ubbcluj.map.domain.Prietenie;
import ro.ubbcluj.map.domain.Tuple;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.PrietenieValidator;
import ro.ubbcluj.map.domain.validators.UtilizatorValidator;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.InMemoryRepository;
import ro.ubbcluj.map.service.UtilizatorService;
import ro.ubbcluj.map.service.PrietenieService;

import java.util.Scanner;

public class Main {


    private static void Meniu()
    {
        System.out.println("1. Adauga utilizator");
        System.out.println("2. Sterge utilizator");
        System.out.println("3. Adauga prieten");
        System.out.println("4. Sterge prieten");
        System.out.println("5. Numar de comunitati");
        System.out.println("6. Cea mai sociabila comunitate");
    }

    public static void main(String[] args) {

        Teste teste = new Teste();
        teste.execute();
        InMemoryRepository<Long, Utilizator> repo = new InMemoryRepository<>(new UtilizatorValidator());
        InMemoryRepository<Tuple<Long, Long>, Prietenie> repoPrietenie = new InMemoryRepository<>(new PrietenieValidator());
        PrietenieService prietenieService = new PrietenieService(repoPrietenie, repo);

            UtilizatorService serv = new UtilizatorService(repo);
        while(true){


            Meniu();
            String cmd;
            Scanner scan = new Scanner(System.in);

            System.out.println("Introdu comanda: ");
            cmd = scan.next();

            switch (cmd) {
                case "1":{
                    String id, nume, prenume;
                    System.out.println("ID:");
                    id= scan.next();

                    System.out.println("Nume:");
                    nume= scan.next();
                    System.out.println("Prenume");
                    prenume= scan.next();

                    try{
                        Utilizator  utilizator = new Utilizator(nume, prenume);
                        utilizator.setId(Long.parseLong(id));
                        serv.adaugaUtilizator(utilizator);
                        System.out.println("Utilizator adaugat!\n");
                    } catch (ValidationException e){
                        System.out.println(e.getMessage());
                    }catch (IllegalArgumentException e){
                        System.out.println(e.toString());
                    }

                    System.out.println(serv.getAll());
                    break;
                }

                case "2":{
                    System.out.println("ID:");
                    String id;
                    id= scan.next();

                    try{
                        prietenieService.stergeUserPrieteni(Long.parseLong(id));
                        serv.stergeUtilizator(Long.parseLong(id));
                        System.out.println("Utilizator sters");
                    }catch (ValidationException e){
                        System.out.println(e.getMessage());
                    }catch (IllegalArgumentException e){
                        System.out.println(e.toString());
                    }

                    System.out.println(serv.getAll());
                    break;
                }

                case "3":{
                    String id1, id2;
                    System.out.println("ID1:");
                    id1= scan.next();
                    System.out.println("ID2:");
                    id2= scan.next();

                    Prietenie prietenie = new Prietenie();
                    prietenie.setId(new Tuple<>(Long.parseLong(id1), Long.parseLong(id2)));

                    try{
                        prietenieService.adaugaPrietenie(prietenie);
                        System.out.println("Prietenie adaugata cu succes");
                    }catch(ValidationException e){
                        System.out.println(e.getMessage());
                    }catch (IllegalArgumentException e){
                        System.out.println(e.toString());
                    }

                    break;
                }

                case "4":{
                    String id1,id2;
                    System.out.println("ID1:");
                    id1= scan.next();
                    System.out.println("ID2:");
                    id2= scan.next();

                    try{
                        prietenieService.stergePrietenie(new Tuple<>(Long.parseLong(id1), Long.parseLong(id2)));
                        System.out.println("Prietenie stearsa cu succes");
                    }catch (ValidationException e){
                        System.out.println(e.getMessage());
                    }catch (IllegalArgumentException e){
                        System.out.println(e.toString());
                    }
                }

                case "5":{
                    System.out.println(prietenieService.numarComunitati());
                }

                case "6":{

                }

                default:
                    System.out.println("Sfarsit");
                    break;

            }
        }
    }
}
