package ro.mpp2024.server;

import ro.mpp2024.*;
import ro.mpp2024.IRepositories.IConfiguratieRepo;
import ro.mpp2024.IRepositories.IJucatorRepo;
import ro.mpp2024.IRepositories.IRundaCurentaRepo;
import ro.mpp2024.IRepositories.IRundaRepo;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServicesImpl implements IServices {

    private IJucatorRepo jucatorRepo;
    private IConfiguratieRepo configuratieRepo;
    private IRundaCurentaRepo rundaCurentaRepo;
    private IRundaRepo rundaRepo;

    private Map<String, IObserver> loggedClients;
    private List<IObserver> observers;

    public ServicesImpl(IJucatorRepo jucatorRepo, IConfiguratieRepo configuratieRepo, IRundaCurentaRepo rundaCurentaRepo, IRundaRepo rundaRepo) {
        this.jucatorRepo = jucatorRepo;
        this.configuratieRepo = configuratieRepo;
        this.rundaCurentaRepo = rundaCurentaRepo;
        this.rundaRepo = rundaRepo;

        loggedClients = new ConcurrentHashMap<>();
        this.observers = new ArrayList<>();

    }


    @Override
    public synchronized void login(ro.mpp2024.Jucator jucator, IObserver client) throws ServiceException {
        Jucator jucatorR = jucatorRepo.findOne(jucator.getId()).orElse(null);
        if (Optional.ofNullable(jucatorR).isPresent()){
            if (loggedClients.get(jucatorR.getId()) != null)
                throw new ServiceException("User already logged in.");
            loggedClients.put(jucatorR.getId(), client);
            observers.add(client);
        } else {
            System.out.println("Authentication failed.");
            throw new ServiceException("Authentication failed.");
        }
    }

    @Override
    public synchronized void logout(ro.mpp2024.Jucator jucator, IObserver client) throws ServiceException {
        IObserver localClient = loggedClients.remove(jucator.getId());
        if (localClient == null)
            throw new ServiceException("User " + jucator.getId() + " is not logged in.");
        observers.remove(client);
    }

    @Override
    public RundaCurenta startGame(Jucator jucator) {
        Integer nrConfigurari = configuratieRepo.getSize();
        Random rand = new Random();
        System.out.println("Nr configurari: " + nrConfigurari);
        int randomValue = rand.nextInt(nrConfigurari);
        System.out.println("Random value: " + randomValue);
        Configuratie configuratie = configuratieRepo.findOne((long) randomValue).orElse(null);
        if (configuratie == null)
            return null;
        System.out.println("Configuratie: " + configuratie.getIndiciu() + " " + configuratie.getLinie() + " " + configuratie.getColoana());
        RundaCurenta r = new RundaCurenta(jucator, 0, configuratie.getIndiciu(), configuratie.getLinie(), configuratie.getColoana());
        UUID uuid = UUID.randomUUID();
        long id = uuid.getMostSignificantBits() & Long.MAX_VALUE;
        r.setId(id);
        rundaCurentaRepo.save(r);
        return r;
    }

    @Override
    public void addRunda(Runda runda) throws ServiceException {
        rundaCurentaRepo.deleteByJucator(runda.getJucator());
        UUID uuid = UUID.randomUUID();
        long id = uuid.getMostSignificantBits() & Long.MAX_VALUE;
        runda.setId(id);
        rundaRepo.save(runda);
        notifyObservers(runda);
    }

    @Override
    public List<Runda> getAllRunde() {
        List<Runda> runde = (List<Runda>) rundaRepo.findAll();
        runde.sort(Comparator.comparing(Runda::getNr_incercari));
        return runde;
    }

    private final int defaultThreadsNo = 5;

    private final ExecutorService executorService = Executors.newFixedThreadPool(defaultThreadsNo);

    private void notifyObservers(Runda runda) {
        for (IObserver observer : observers) {
            executorService.execute(() -> {
                observer.newRunda(runda);
            });
        }
    }
}
