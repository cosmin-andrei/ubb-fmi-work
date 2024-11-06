package ro.mpp2024.server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;
import ro.mpp2024.repository.interfaces.JucatorRepoInterface;
import ro.mpp2024.repository.interfaces.RundaRepoInterface;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class ServicesImpl implements IServices {

    private static final Logger logger = LogManager.getLogger();
    private JucatorRepoInterface jucatorRepo;
    private Map<String, IObserver> loggedClients;
    private RundaRepoInterface rundaRepo;

    private List<IObserver> observers;

    public ServicesImpl(JucatorRepoInterface jucatorRepo, RundaRepoInterface rundaRepo) {
        this.jucatorRepo = jucatorRepo;
        this.rundaRepo = rundaRepo;
        loggedClients = new ConcurrentHashMap<>();
        this.observers = new ArrayList<>();
    }


    @Override
    public synchronized void login(Jucator jucator, IObserver client) throws ServiceException {
        logger.info("Login request: " + jucator);
        Jucator userR = jucatorRepo.findOne(jucator.getId()).orElse(null);
        if (userR != null) {
            if (loggedClients.get(userR.getId()) != null) {
                logger.error("User already logged in.");
                throw new ServiceException("User already logged in.");
            }
            loggedClients.put(userR.getId(), client);
            observers.add(client);
        } else {
            logger.error("Authentication failed.");
            throw new ServiceException("Authentication failed.");

        }
    }

    @Override
    public synchronized void logout(Jucator jucator, IObserver client) throws ServiceException {
        logger.info("Logout request: " + jucator);
        IObserver localClient = loggedClients.remove(jucator.getId());
        if (localClient == null) {
            logger.error("User " + jucator.getId() + " is not logged in.");
            throw new ServiceException("User " + jucator.getId() + " is not logged in.");
        }
    }

    @Override
    public Long chooseMove(Jucator jucator, Map<Long, String> board) throws ServiceException {
        logger.info("Choose move request: " + jucator);
        Random random = new Random();
        long move = random.nextLong(9) + 1;
        while (!Objects.equals(board.get(move), "")) {
            move = random.nextLong(9) + 1;
        }
        return move;
    }

    @Override
    public String verifyGameWin(Map<Long, String> board) {
        if ((Objects.equals(board.get(1L), board.get(2L))) && (Objects.equals(board.get(2L), board.get(3L))) && !Objects.equals(board.get(3L), "")) {
            return board.get(1L);
        }
        if (Objects.equals(board.get(4L), board.get(5L)) && Objects.equals(board.get(5L), board.get(6L)) && !Objects.equals(board.get(6L), "")) {
            return board.get(4L);
        }
        if (Objects.equals(board.get(7L), board.get(8L)) && Objects.equals(board.get(8L), board.get(9L)) && !Objects.equals(board.get(9L), "")) {
            return board.get(7L);
        }
        if (Objects.equals(board.get(1L), board.get(4L)) && Objects.equals(board.get(4L), board.get(7L)) && !Objects.equals(board.get(7L), "")) {
            return board.get(1L);
        }
        if (Objects.equals(board.get(2L), board.get(5L)) && board.get(5L) == board.get(8L) && !Objects.equals(board.get(8L), "")) {
            return board.get(2L);
        }
        if (Objects.equals(board.get(3L), board.get(6L)) && board.get(6L) == board.get(9L) && !Objects.equals(board.get(9L), "")) {
            return board.get(3L);
        }
        if (Objects.equals(board.get(1L), board.get(5L)) && Objects.equals(board.get(5L), board.get(9L)) && !Objects.equals(board.get(9L), "")) {
            return board.get(1L);
        }
        if (Objects.equals(board.get(3L), board.get(5L)) && Objects.equals(board.get(5L), board.get(7L)) && !Objects.equals(board.get(7L), ""))
            return board.get(3L);
        return "";
    }

    @Override
    public void addRunda(Runda runda) {
        rundaRepo.save(runda);
    }

    @Override
    public List<Runda> getAllRunda() {
        return (List<Runda>) rundaRepo.findAll();
    }

//
//    private final int defaultThreadsNo = 5;
//
//    private final ExecutorService executorService = Executors.newFixedThreadPool(defaultThreadsNo);
//
//    private void notifyAll() {
//        for (IObserver observer : observers) {
//            executorService.execute(() -> {
//                try {
//                    observer.newDonator(donator);
//                } catch (ServiceException e) {
//                    System.err.println("Error notifying donator: " + e.getMessage());
//                }
//            });
//        }
//    }
}
