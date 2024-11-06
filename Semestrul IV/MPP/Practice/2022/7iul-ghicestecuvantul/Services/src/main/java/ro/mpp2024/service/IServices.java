package ro.mpp2024.service;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;

import java.util.List;

public interface IServices {

    void login(Jucator jucator, IObserver client) throws ServiceException;
    void logout(Jucator jucator, IObserver client) throws ServiceException;

    List<Jucator> getJucatori() throws ServiceException;

    String getPropuneri() throws ServiceException;

    void saveConfiguration(Configuratie configuratie) throws ServiceException;

    Configuratie getConfiguratie(String id) throws ServiceException;
}
