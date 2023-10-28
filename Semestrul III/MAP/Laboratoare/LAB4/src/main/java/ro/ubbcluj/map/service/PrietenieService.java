package ro.ubbcluj.map.service;

import ro.ubbcluj.map.domain.Prietenie;
import ro.ubbcluj.map.domain.Tuple;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.Repository;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class PrietenieService {

    private Repository<Long, Utilizator> repoUtilizator;
    private Repository<Tuple<Long, Long>, Prietenie> repoPrietenie;

    public PrietenieService(Repository<Tuple<Long, Long>, Prietenie> repoPrietenie, Repository<Long, Utilizator> repoUtilizator) {
        this.repoUtilizator = repoUtilizator;
        this.repoPrietenie = repoPrietenie;
    }

    public void adaugaPrietenie(Prietenie prietenie) {

        Long id_user1 = prietenie.getId().getLeft();
        Optional<Utilizator> user1 = repoUtilizator.findOne(id_user1);
        if (user1.isEmpty())
            throw new ValidationException("Id inexistent!\n");

        Long id_user2 = prietenie.getId().getRight();
        Optional<Utilizator> user2 = repoUtilizator.findOne(id_user2);
        if (user2.isEmpty())
            throw new ValidationException("ID Inexistent!\n");

        Optional<Prietenie> verificare_dublura = repoPrietenie.findOne(new Tuple<>(id_user1, id_user2));
        if (verificare_dublura.isPresent())
            throw new ValidationException("ID existent\n");

        repoPrietenie.save(prietenie);


    }

    public void stergePrietenie(Tuple<Long, Long> id) {

        Long id_user1 = id.getLeft();
        Optional<Utilizator> user1 = repoUtilizator.findOne(id_user1);
        if (user1.isEmpty())
            throw new ValidationException("Id inexistent!\n");

        Long id_user2 = id.getRight();
        Optional<Utilizator> user2 = repoUtilizator.findOne(id_user2);
        if (user2.isEmpty())
            throw new ValidationException("ID Inexistent!\n");

        Optional<Prietenie> verificare = repoPrietenie.findOne(id);
        if (verificare.isPresent()) {
            repoPrietenie.delete(id);
        }

    }

    public boolean verificaExistenta(Tuple<Long, Long> id) {
        Optional<Prietenie> prietenie = repoPrietenie.findOne(id);
        return prietenie.isPresent();
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

        for(Prietenie prietenie : repoPrietenie.findAll()){
            Long id1 = prietenie.getId().getLeft();
            Long id2 = prietenie.getId().getRight();
            if(Objects.equals(id1, userID)) {
                idsToDelete.add(prietenie.getId());
            }
            if (Objects.equals(id2, userID)) {
                idsToDelete.add(prietenie.getId());
            }
        }

        for (Tuple<Long, Long> idToDelete : idsToDelete) {
            repoPrietenie.delete(idToDelete);
        }
    }
}