package ro.ubbcluj.map.socialnetwork.service;

import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.domain.validators.ValidationException;
import ro.ubbcluj.map.socialnetwork.observer.Observable;
import ro.ubbcluj.map.socialnetwork.observer.Observer;
import ro.ubbcluj.map.socialnetwork.repository.Repository;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class UtilizatorService implements Observable {

    Repository<Long, Utilizator> repo;
    List<Observer> observers = new ArrayList<>();

    public UtilizatorService(Repository<Long, Utilizator> repo) {
        this.repo = repo;
    }

    public void adaugaUtilizator(Utilizator utilizator) throws SQLException {
        repo.findAll().forEach(it -> {
            if (Objects.equals(it.getId(), utilizator.getId()))
                throw new ValidationException("Exista un utilizator cu acest ID");
        });
        repo.save(utilizator);
        notifyAllObservers();

    }

    public void stergeUtilizator(Long id) throws SQLException {
        repo.delete(id);
        notifyAllObservers();
    }

    public void updateUtilizator(Utilizator utilizator) throws SQLException {

        if(repo.findOne(utilizator.getId()).isEmpty())
            throw new ValidationException("Utilizatorul nu exista");

        repo.update(utilizator);
        notifyAllObservers();
  }

    public List<Utilizator> getAll() throws SQLException {

        List<Utilizator> rez = new ArrayList<>();
        repo.findAll().forEach(rez::add);
        return rez;

    }

    @Override
    public void registerObserver(Observer o) {
        observers.add(o);
    }

    @Override
    public void removeObserver(Observer o) {
        observers.remove(o);
    }

    @Override
    public void notifyAllObservers() throws SQLException {
        for (Observer observer : observers) {
            observer.update();
        }
    }
}
