package ro.ubbcluj.map.service;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.UtilizatorValidator;
import ro.ubbcluj.map.repository.InMemoryRepository;

import java.util.ArrayList;
import java.util.List;

public class UtilizatorService {

    private InMemoryRepository<Long, Utilizator> repo = new InMemoryRepository<>(new UtilizatorValidator());
    public UtilizatorService(InMemoryRepository<Long, Utilizator> repo) {
        this.repo = repo;
    }

    public void adaugaUtilizator(Utilizator utilizator)
    {
        repo.save(utilizator);
    }

    public void stergeUtilizator(Long id){
        repo.delete(id);
    }

    public int getAll(){
        Iterable<Utilizator> utilizatori = repo.findAll();

        int k=0;

        for(Utilizator it: utilizatori){
            k++;
        }

        return k;

    }



}
