package ro.ubbcluj.map.service;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.InMemoryRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class UtilizatorService {

    private InMemoryRepository<Long, Utilizator> repo;

    public UtilizatorService(InMemoryRepository<Long, Utilizator> repo) {
        this.repo = repo;
    }

    public void adaugaUtilizator(Utilizator utilizator)
    {
        repo.findAll().forEach(it->{
            if(Objects.equals(it.getId(), utilizator.getId()))
                throw new ValidationException("Exista un utilizator cu acest ID");
        });
        repo.save(utilizator);
    }

    public void stergeUtilizator(Long id){

        boolean ok= getAll().stream()
                .anyMatch(it->Objects.equals(it.getId(), id));

        if(ok){
            repo.delete(id);
        }else
            throw new ValidationException("Utilizatorul cu acest id nu exista \n");
    }

    public List<Utilizator> getAll(){

        List<Utilizator> rez = new ArrayList<>();
        repo.findAll().forEach(rez::add);
        return rez;

    }

}
