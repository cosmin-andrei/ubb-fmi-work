package ro.mpp2024.server;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Cuvant;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;
import ro.mpp2024.repository.CuvantRepo;
import ro.mpp2024.repository.RundaRepo;
import ro.mpp2024.repository.interfaces.CuvantRepoInterface;
import ro.mpp2024.repository.interfaces.JucatorRepoInterface;
import ro.mpp2024.repository.interfaces.RundaRepoInterface;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServicesImpl implements IServices {

    private JucatorRepoInterface jucatorRepo;
    private CuvantRepoInterface cuvantRepo;
    private RundaRepoInterface rundaRepo;
    private Map<String, IObserver> loggedClients;

    private List<IObserver> observers;

    public ServicesImpl(JucatorRepoInterface jucatorRepo, CuvantRepoInterface cuvantRepo, RundaRepoInterface rundaRepo) {
        this.jucatorRepo = jucatorRepo;
        this.cuvantRepo = cuvantRepo;
        this.rundaRepo = rundaRepo;
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
    public Configuratie startGame(Jucator jucator) throws ServiceException {
        List<Cuvant> cuvinte = cuvantRepo.generateWords(5);
        for (int i = 0; i < 5; i++) {
            cuvinte.add(cuvinte.get(i));
        }
        Collections.shuffle(cuvinte);

        Configuratie configuratie = new Configuratie(cuvinte.get(0), cuvinte.get(1), cuvinte.get(2), cuvinte.get(3), cuvinte.get(4),
                cuvinte.get(5), cuvinte.get(6), cuvinte.get(7), cuvinte.get(8), cuvinte.get(9));
        UUID uuid = UUID.randomUUID();
        Long id = uuid.getMostSignificantBits() & Long.MAX_VALUE;

        configuratie.setId(id);

        System.out.println(configuratie.getPoz1());

        Runda runda = new Runda(jucator, 0);
        runda.setId(id);
        rundaRepo.save(runda);
        notifyObservers(runda);
        configuratie.setRunda(runda);

        return configuratie;

    }

    @Override
    public Runda getRunda(Long id) {
        return rundaRepo.findOne(id).orElse(null);
    }

    @Override
    public void updateRunda(Runda runda) {
        rundaRepo.update(runda);
        notifyObservers(runda);
    }

    @Override
    public List<Runda> getClasament() throws ServiceException {
        List<Runda> runde = (List<Runda>) rundaRepo.findAll();
        runde.sort(Comparator.comparing(Runda::getScor));
        return runde;
    }

    private void notifyObservers(Runda runda) {
        for (IObserver observer : observers) {
            executorService.execute(() -> {
                observer.newRunda(runda);
            });
        }
    }
    private final int defaultThreadsNo = 5;

    private final ExecutorService executorService = Executors.newFixedThreadPool(defaultThreadsNo);

}
