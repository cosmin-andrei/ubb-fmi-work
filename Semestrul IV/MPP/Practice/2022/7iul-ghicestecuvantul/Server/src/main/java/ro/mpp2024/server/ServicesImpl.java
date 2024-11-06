package ro.mpp2024.server;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.repository.interfaces.ConfiguratieRepoInterface;
import ro.mpp2024.repository.interfaces.JucatorRepoInterface;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class ServicesImpl implements IServices {

    private JucatorRepoInterface jucatorRepo;
    private ConfiguratieRepoInterface configuratieRepo;
    private Map<String, IObserver> loggedClients;
    private Map<String, Configuratie> configuratii;

    private List<IObserver> observers;

    public ServicesImpl(JucatorRepoInterface jucatorRepo, ConfiguratieRepoInterface configuratieRepo) {
        this.jucatorRepo = jucatorRepo;
        this.configuratieRepo = configuratieRepo;
        loggedClients = new ConcurrentHashMap<>();
        this.observers = new ArrayList<>();
    }


    @Override
    public synchronized void login(Jucator jucator, IObserver client) throws ServiceException {
        Jucator userR = jucatorRepo.findOne(jucator.getId()).orElse(null);
        if (userR != null) {
            if (loggedClients.get(userR.getId()) != null)
                throw new ServiceException("User already logged in.");
            loggedClients.put(userR.getId(), client);
            observers.add(client);
        } else
            throw new ServiceException("Authentication failed.");
    }

    @Override
    public synchronized void logout(Jucator jucator, IObserver client) throws ServiceException {
        IObserver localClient = loggedClients.remove(jucator.getId());
        if (localClient == null)
            throw new ServiceException("User " + jucator.getId() + " is not logged in.");
    }

    @Override
    public List<Jucator> getJucatori() {
        List<Jucator> jucatori = new ArrayList<>();
        for (String id : loggedClients.keySet()) {
            jucatori.add(new Jucator(id));
        }
        return jucatori;
    }

    @Override
    public String getPropuneri() {
        String input = "!~@#$%^&*()_+{}:/?";
        return getRandomCharacters(input);

    }

    @Override
    public void saveConfiguration(Configuratie configuratie) {
        configuratieRepo.save(configuratie);
    }

    @Override
    public Configuratie getConfiguratie(String id) {
        return configuratieRepo.findByPlayer(id).orElse(null);
    }

    private String getRandomCharacters(String input) {
        Random random = new Random();
        StringBuilder selectedChars = new StringBuilder(4);

        for (int i = 0; i < 4; i++) {
            int randomIndex = random.nextInt(input.length());
            selectedChars.append(input.charAt(randomIndex));
        }

        return selectedChars.toString();
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
