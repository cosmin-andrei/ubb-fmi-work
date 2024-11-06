package ro.mpp2024.service;

import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.util.List;
import java.util.Map;

public interface IServices {

    void login(Jucator jucator, IObserver client) throws ServiceException;
    void logout(Jucator jucator, IObserver client) throws ServiceException;

    Long chooseMove(Jucator jucator, Map<Long, String> board) throws ServiceException;

    String verifyGameWin(Map<Long, String> board) throws ServiceException;

    void addRunda(Runda runda) throws ServiceException;

    List<Runda> getAllRunda() throws ServiceException;
}
