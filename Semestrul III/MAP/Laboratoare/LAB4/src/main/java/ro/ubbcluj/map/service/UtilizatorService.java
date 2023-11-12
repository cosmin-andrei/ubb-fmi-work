package ro.ubbcluj.map.service;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.UtilizatorValidator;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.Repository;
import ro.ubbcluj.map.repository.database.UserDBRepository;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class UtilizatorService {

//    private InMemoryRepository<Long, Utilizator> repo;

    Repository<Long, Utilizator> repo;

    public UtilizatorService(Repository<Long, Utilizator> repo) {
        this.repo = repo;
    }

    public void adaugaUtilizator(Utilizator utilizator) throws SQLException {
        repo.findAll().forEach(it->{
            if(Objects.equals(it.getId(), utilizator.getId()))
                throw new ValidationException("Exista un utilizator cu acest ID");
        });
        repo.save(utilizator);
    }

    public void stergeUtilizator(Long id) throws SQLException {
        repo.delete(id);
    }

    public List<Utilizator> getAll() throws SQLException {

        List<Utilizator> rez = new ArrayList<>();
        repo.findAll().forEach(rez::add);
        return rez;

    }

}
