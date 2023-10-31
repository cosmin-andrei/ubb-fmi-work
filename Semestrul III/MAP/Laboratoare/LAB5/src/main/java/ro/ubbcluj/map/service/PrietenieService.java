package ro.ubbcluj.map.service;

import ro.ubbcluj.map.domain.*;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.Repository;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class PrietenieService {

    private Repository<Long, Utilizator> repoUtilizator;
    private Repository<Tuple<Long, Long>, Prietenie> repoPrietenie;

    public PrietenieService(Repository<Tuple<Long, Long>, Prietenie> repoPrietenie, Repository<Long, Utilizator> repoUtilizator) {
        this.repoUtilizator = repoUtilizator;
        this.repoPrietenie = repoPrietenie;


        //stochez toate prieteniile existente in friends din utilizator
        repoPrietenie.findAll().forEach(prietenie -> {
            Utilizator u1 = this.repoUtilizator.findOne(prietenie.getId().getLeft()).get();
            Utilizator u2 = this.repoUtilizator.findOne(prietenie.getId().getRight()).get();
            u1.getFriends().add(u2);
            u2.getFriends().add(u1);
        });
    }

    public void adaugaPrietenie(Prietenie prietenie) {

        //verific sa nu existe deja prietenie intre cei doi useri
        boolean exist = GetAll().stream()
                .anyMatch(it->Objects.equals(prietenie.getId(), it.getId()));
        if(exist)
            throw new ValidationException("Exista deja o prietenie!\n");

        //setez prietenia
        Utilizator user1 = repoUtilizator.findOne(prietenie.getId().getLeft()).get();
        Utilizator user2 = repoUtilizator.findOne(prietenie.getId().getRight()).get();
        repoPrietenie.save(prietenie);
        user1.getFriends().add(user2);
        user2.getFriends().add(user1);

    }

    public void stergePrietenie(Tuple<Long, Long> id) {

        //verific daca exita prietenia
        boolean exist = GetAll().stream()
                .anyMatch(it->Objects.equals(id, it.getId()));


        if(exist) {
            Utilizator user1 = repoUtilizator.findOne(id.getLeft()).get();
            Utilizator user2 = repoUtilizator.findOne(id.getRight()).get();
            user1.getFriends().remove(user2);
            user2.getFriends().remove(user1);
            repoPrietenie.delete(id);
        }
        else{
            throw new ValidationException("Prietenia nu exista!\n");
        }

    }

    //functie teste
    public boolean verificaExistenta(Tuple<Long, Long> id) {
        return repoPrietenie.findOne(id).isPresent();
    }

    public int numarComunitati() {

        List<Long> utilizatoriVizitati = new ArrayList<>();
        List<Utilizator> all = GetAllUser();
        int numarComunitati = (int) all.stream()
                .filter(user -> !utilizatoriVizitati.contains(user.getId()))
                  //ca forEach (op term), peek-operatie intermediara
                .peek(user->{
                    List<Utilizator> comunitateC = new ArrayList<>();
                    DFS(user.getId(), utilizatoriVizitati, comunitateC);
                })
                .count();

        return numarComunitati;
    }

    private List<Utilizator> GetAllUser() {
        List<Utilizator> rez = new ArrayList<>();
        repoUtilizator.findAll().forEach(rez::add);
        return rez;
    }


    public String ComunitateSociabila(){

        List<Long> useriVizitati = new ArrayList<>();

        //variabila atomica - poate fi accesata si modificata de mai multe threaduri
        AtomicInteger max= new AtomicInteger(-1);
        Iterable<Utilizator> all = repoUtilizator.findAll();

        //aici salvez comunitatea sociabila
        AtomicReference<List<Utilizator>> comunitateSociabila = new AtomicReference<>(new ArrayList<>());
        StringBuilder rez = new StringBuilder();

        all.forEach(it->{
            if(!useriVizitati.contains(it.getId())){
                List<Utilizator> comunitateCurenta = new ArrayList<>();
                DFS(it.getId(), useriVizitati, comunitateCurenta);

                if (comunitateCurenta.size() > max.get()) {
                    max.set(comunitateCurenta.size());
                    comunitateSociabila.set(comunitateCurenta);
                }
            }
        });

        //construim string-ul pt return
        comunitateSociabila.get().forEach(user-> rez.append(user.getFirstName()).append(" ").append(user.getLastName()).append("  "));

        return rez.toString();

    }


    private List<Prietenie> GetAll(){
        List<Prietenie> rez=new ArrayList<>();
        repoPrietenie.findAll().forEach(rez::add);
        return rez;
    }

    private void DFS(Long userId, List<Long> utilizatoriVizitati, List<Utilizator> comunitateCurenta) {

        utilizatoriVizitati.add(userId);

        Utilizator user = repoUtilizator.findOne(userId).get();
        comunitateCurenta.add(user);

        List<Prietenie> prietenii = GetAll();

        prietenii.stream()
                .filter(prietenie -> prietenie.getId().getLeft().equals(userId)  || prietenie.getId().getRight().equals(userId))
                .forEach(prietenie->
                {Long prietenId = (prietenie.getId().getLeft().equals(userId) ? prietenie.getId().getRight() : prietenie.getId().getLeft());
                    if (!utilizatoriVizitati.contains(prietenId)) {
                        DFS(prietenId, utilizatoriVizitati, comunitateCurenta);
                    }
                });
    }


    public void stergeUserPrieteni(Long userID){

        List<Tuple<Long,Long>> idsToDelete = new ArrayList<>();

        Utilizator user1 = repoUtilizator.findOne(userID).get();
        repoPrietenie.findAll().forEach(prietenie -> {

            if(Objects.equals(prietenie.getId().getLeft(), userID) ||
                    Objects.equals(prietenie.getId().getRight(), userID)) {
                Long prietenID = prietenie.getId().getLeft().equals(userID) ?
                        prietenie.getId().getRight() :
                        prietenie.getId().getLeft();


                Utilizator user2 = repoUtilizator.findOne(prietenID).get();

                user1.getFriends().remove(user2);
                user2.getFriends().remove(user1);
                idsToDelete.add(prietenie.getId());
                }
        });

        idsToDelete.forEach(repoPrietenie::delete);

    }
}