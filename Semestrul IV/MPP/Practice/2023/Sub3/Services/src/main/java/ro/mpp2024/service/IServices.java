package ro.mpp2024.service;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.util.List;

public interface IServices {

    void login(Jucator jucator, IObserver client) throws ServiceException;
    void logout(Jucator jucator, IObserver client) throws ServiceException;
    Configuratie startGame(Jucator jucator) throws ServiceException;
    Runda getRunda(Long id) throws ServiceException;
    void updateRunda(Runda runda) throws ServiceException;

    List<Runda> getClasament() throws ServiceException;
}
