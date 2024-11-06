package ro.mpp2024;

import java.util.List;

public interface IServices {

    void login(Jucator jucator, IObserver client) throws ServiceException;
    void logout (Jucator jucator, IObserver client) throws ServiceException;


    RundaCurenta startGame(Jucator jucator) throws ServiceException;

    void addRunda(Runda runda) throws ServiceException;

    List<Runda> getAllRunde() throws ServiceException;
}
