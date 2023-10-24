package ro.ubbcluj.map.service;

import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.UtilizatorValidator;
import ro.ubbcluj.map.repository.InMemoryRepository;
import ro.ubbcluj.map.repository.Repository;
import java.util.ArrayList;
import java.util.List;

public class UtilizatorService {

    private InMemoryRepository<Long, Utilizator> repo = new InMemoryRepository<>(new UtilizatorValidator());

    public UtilizatorService(InMemoryRepository<Long, Utilizator> repo) {
        this.repo = repo;
    }

    public Utilizator adaugaUtilizator(Utilizator utilizator)
    {
        return repo.save(utilizator);
    }

    public Utilizator stergeUtilizator(Long id){
        return repo.delete(id);
    }

    public int getAll(){
        Iterable<Utilizator> utilizatori = repo.findAll();
        List<Utilizator> rez = new ArrayList<Utilizator>();

        int k=0;

        for(Utilizator it: utilizatori){
            k++;
        }

        return k;

    }



}
