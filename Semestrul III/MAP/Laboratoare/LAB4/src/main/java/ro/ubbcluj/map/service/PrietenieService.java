package ro.ubbcluj.map.service;

import com.jogamp.common.util.Bitfield;
import ro.ubbcluj.map.domain.Prietenie;
import ro.ubbcluj.map.domain.Tuple;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.Repository;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class PrietenieService {

    private Repository<Long, Utilizator> repoUtilizator;
    private Repository<Tuple<Long, Long>, Prietenie> repoPrietenie;

    public PrietenieService(Repository<Tuple<Long, Long>, Prietenie> repoPrietenie, Repository<Long, Utilizator> repoUtilizator) {
        this.repoUtilizator = repoUtilizator;
        this.repoPrietenie = repoPrietenie;
    }

    public Prietenie adaugaPrietenie(Prietenie prietenie) {

        Long id_user1 = prietenie.getId().getLeft();
        Utilizator user1 = repoUtilizator.findOne(id_user1);
        if (user1 == null)
            throw new ValidationException("Id inexistent!\n");

        Long id_user2 = prietenie.getId().getRight();
        Utilizator user2 = repoUtilizator.findOne(id_user2);
        if (user2 == null)
            throw new ValidationException("ID Inexistent!\n");

        Prietenie verificare_dublura = repoPrietenie.findOne(new Tuple(id_user1, id_user2));
        if (verificare_dublura != null)
            throw new ValidationException("ID existent\n");

//        user1.getFriends().add(user2);
//        user2.getFriends().add(user1);
        return repoPrietenie.save(prietenie);


    }

    public Prietenie stergePrietenie(Tuple<Long, Long> id) {

        Long id_user1 = id.getLeft();
        Utilizator user1 = repoUtilizator.findOne(id_user1);
        if (user1 == null)
            throw new ValidationException("Id inexistent!\n");

        Long id_user2 = id.getRight();
        Utilizator user2 = repoUtilizator.findOne(id_user2);
        if (user2 == null)
            throw new ValidationException("ID Inexistent!\n");

        Prietenie verificare = repoPrietenie.findOne(id);
        if (verificare != null) {
//            user1.getFriends().remove(user2);
//            user2.getFriends().remove(user1);
            return repoPrietenie.delete(id);
        }

        return null;
    }

    public boolean verificaExistenta(Tuple<Long, Long> id) {
        Prietenie prietenie = repoPrietenie.findOne(id);
        return prietenie != null;
    }

    public int numarComunitati() {
        List<Long> utilizatoriVizitati = new ArrayList<>();
        int numarComunitati = 0;

        for (Utilizator utilizator : repoUtilizator.findAll()) {
            Long userId = utilizator.getId();
            if (!utilizatoriVizitati.contains(userId)) {
                DFS(userId, utilizatoriVizitati);
                numarComunitati = numarComunitati + 1;
            }
        }

        return numarComunitati;
    }

//    public List<Integer> Sociabila(){
//        List<Long> utilizatoriVizitati = new ArrayList<>();
//        int numarComunitati = 0;
//
//        for (Utilizator utilizator : repoUtilizator.findAll()) {
//            Long userId = utilizator.getId();
//            if (!utilizatoriVizitati.contains(userId)) {
//                DFS(userId, utilizatoriVizitati);
//                numarComunitati = numarComunitati + 1;
//            }
//        }
//
//        return numarComunitati;
//    }

    private void DFS(Long userId, List<Long> utilizatoriVizitati) {
        utilizatoriVizitati.add(userId);
        for (Prietenie prietenie : repoPrietenie.findAll()) {
            if (prietenie.getId().getLeft().equals(userId)) {
                Long prietenId = prietenie.getId().getRight();
                if (!utilizatoriVizitati.contains(prietenId)) {
                    DFS(prietenId, utilizatoriVizitati);
                }
            }

            if (prietenie.getId().getRight().equals(userId)) {
                Long prietenId = prietenie.getId().getLeft();
                if (!utilizatoriVizitati.contains(prietenId)) {
                    DFS(prietenId, utilizatoriVizitati);
                }
            }
        }
    }


    public void stergeUserPrieteni(Long userID){

        List<Tuple<Long, Long>> idsToDelete = new ArrayList<>();

//        System.out.println(repoPrietenie.findAll());
        for(Prietenie prietenie : repoPrietenie.findAll()){
            Long id1 = prietenie.getId().getLeft();
            Long id2 = prietenie.getId().getRight();
            if(id1 == userID) {
                idsToDelete.add(prietenie.getId());
            }
            if (id2 == userID) {
                idsToDelete.add(prietenie.getId());
            }
        }

        for (Tuple<Long, Long> idToDelete : idsToDelete) {
            repoPrietenie.delete(idToDelete);
        }

//        for(Utilizator friend: friends){
//            Tuple<Long, Long> pr1 = new Tuple<>(userID, friend.getId());
//            Tuple<Long, Long> pr2 = new Tuple<>(friend.getId(),userID);
//            Prietenie p1 = repoPrietenie.findOne(pr1);
//            Prietenie p2 = repoPrietenie.findOne(pr2);
//            if(p1!=null){
//                stergePrietenie(pr1);
//            }
//            else if(p2!=null){
//                stergePrietenie(pr2);
//            }
//
//        }
    }
}