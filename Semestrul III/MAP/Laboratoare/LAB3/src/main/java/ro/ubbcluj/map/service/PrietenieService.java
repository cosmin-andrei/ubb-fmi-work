package ro.ubbcluj.map.service;

import ro.ubbcluj.map.domain.Prietenie;
import ro.ubbcluj.map.domain.Tuple;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.Repository;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class PrietenieService {

    private Repository<Long, Utilizator> repoUtilizator;
    private Repository<Tuple<Long,Long>, Prietenie> repoPrietenie;

    public PrietenieService(Repository<Tuple<Long, Long>, Prietenie> repoPrietenie, Repository<Long, Utilizator> repoUtilizator) {
        this.repoUtilizator = repoUtilizator;
        this.repoPrietenie = repoPrietenie;
    }

    public Prietenie adaugaPrietenie(Prietenie prietenie){

        Long id_user1 = prietenie.getId().getLeft();
        Utilizator user1 = repoUtilizator.findOne(id_user1);
        if(user1==null)
            throw new ValidationException("Id inexistent!\n");

        Long id_user2 = prietenie.getId().getRight();
        Utilizator user2 = repoUtilizator.findOne(id_user2);
        if(user2 == null)
            throw new ValidationException("ID Inexistent!\n");

        Prietenie verificare_dublura = repoPrietenie.findOne(new Tuple(id_user1, id_user2));
        if(verificare_dublura != null)
            throw new ValidationException("ID existent\n");

        return repoPrietenie.save(prietenie);


    }

    public Prietenie stergePrietenie(Tuple<Long, Long> id){

        Long  id_user1 = id.getLeft();
        Utilizator user1 = repoUtilizator.findOne(id_user1);
        if(user1==null)
            throw new ValidationException("Id inexistent!\n");

        Long id_user2 = id.getRight();
        Utilizator user2 = repoUtilizator.findOne(id_user2);
        if(user2 == null)
            throw new ValidationException("ID Inexistent!\n");

        Prietenie verificare = repoPrietenie.findOne(id);
        if(verificare != null) {
            return repoPrietenie.delete(id);
        }

        return null;
    }

    public boolean verificaExistenta(Tuple<Long, Long> id){
        Prietenie prietenie = repoPrietenie.findOne(id);
        return prietenie!=null;
    }
    public int numarComunitati() {
        List<Long> utilizatoriVizitati = new ArrayList<>();
        int numarComunitati = 0;

        for (Utilizator utilizator : repoUtilizator.findAll()) {
            Long userId = utilizator.getId();
            if (!utilizatoriVizitati.contains(userId)) {
                numarComunitati = numarComunitati + 1;
                DFS(userId, utilizatoriVizitati);
            }
        }

        return numarComunitati;
    }

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
}