package ro.ubbcluj.map.service;

import ro.ubbcluj.map.domain.Prietenie;
import ro.ubbcluj.map.domain.Tuple;
import ro.ubbcluj.map.domain.Utilizator;
import ro.ubbcluj.map.domain.validators.ValidationException;
import ro.ubbcluj.map.repository.Repository;

import java.sql.SQLException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class PrietenieService {

//    private Repository<Long, Utilizator> repoUtilizator;
//    private Repository<Tuple<Long, Long>, Prietenie> repoPrietenie;

    Repository<Long, Utilizator> repoUtilizator;

    Repository<Tuple<Long, Long>, Prietenie> repoPrietenie ;
    public PrietenieService(Repository<Long, Utilizator> repoUtilizator, Repository<Tuple<Long, Long>, Prietenie> repoPrietenie) throws SQLException {
        this.repoUtilizator = repoUtilizator;
        this.repoPrietenie = repoPrietenie;


        //stochez toate prieteniile existente in friends din utilizator
        repoPrietenie.findAll().forEach(prietenie -> {
            Utilizator u1;
            try {
                u1 = this.repoUtilizator.findOne(prietenie.getId().getLeft()).get();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            Utilizator u2;
            try {
                u2 = this.repoUtilizator.findOne(prietenie.getId().getRight()).get();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            u1.getFriends().add(u2);
            u2.getFriends().add(u1);
        });

    }

    public void adaugaPrietenie(Prietenie prietenie) throws SQLException {

        //verific sa nu existe deja prietenie intre cei doi useri
        boolean exist = GetAll().stream()
                .anyMatch(it->Objects.equals(prietenie.getId(), it.getId()));
        if(exist)
            throw new ValidationException("Exista deja o prietenie!\n");

        //setez prietenia
        Utilizator user1 = repoUtilizator.findOne(prietenie.getId().getLeft()).get();
        Utilizator user2 = repoUtilizator.findOne(prietenie.getId().getRight()).get();
        repoPrietenie.save(prietenie);
        user1.getFriends().add(user2);
        user2.getFriends().add(user1);

    }

    public List<Tuple<Utilizator, LocalDate>> GetFriendsByMonth(Long userID, int Month) throws SQLException {

        List<Tuple<Utilizator, LocalDate>> userFriends = new ArrayList<>();
        List<Prietenie> allFriends = (List<Prietenie>) repoPrietenie.findAll();
        allFriends.stream()
                .filter(friend -> (friend.getId().getLeft() == userID || friend.getId().getRight() == userID) && friend.getDate().getMonth().getValue() - 1 == Month)
//                {
//                    if((friend.getId().getLeft() == userID || friend.getId().getRight() == userID) && friend.getDate().getMonth().getValue() == Month)
//                        return true;
//                    return false;
//                }
//                )
                .map(friend -> {
                    if(friend.getId().getRight() == userID)
                        return new Tuple<Long, LocalDate>(friend.getId().getLeft(), friend.getDate().toLocalDate());
                    return new Tuple<Long, LocalDate>(friend.getId().getRight(), friend.getDate().toLocalDate());
                })
                .forEach(tuple-> {
                    try {
                        Utilizator user = repoUtilizator.findOne(tuple.getLeft()).get();
                        userFriends.add(new Tuple<Utilizator, LocalDate>(user, tuple.getRight()));
                    } catch (SQLException e) {
                        throw new RuntimeException(e);
                    }
                });

        return userFriends;

    }

    public void stergePrietenie(Tuple<Long, Long> id) throws SQLException {

//        //verific daca exita prietenia
//        boolean exist = GetAll().stream()
//                .anyMatch(it->Objects.equals(id, it.getId()));
//
//
//        if(exist) {
//            Utilizator user1 = repoUtilizator.findOne(id.getLeft()).get();
//            Utilizator user2 = repoUtilizator.findOne(id.getRight()).get();
//            user1.getFriends().remove(user2);
//            user2.getFriends().remove(user1);
//            repoPrietenie.delete(id);
//        }
//        else{
//            throw new ValidationException("Prietenia nu exista!\n");
//        }

    }

    //functie teste
    public boolean verificaExistenta(Tuple<Long, Long> id) throws SQLException {
        return repoPrietenie.findOne(id).isPresent();
    }

    public int numarComunitati() throws SQLException {

        List<Long> utilizatoriVizitati = new ArrayList<>();
        List<Utilizator> all = GetAllUser();

        return (int) all.stream()
                .filter(user -> !utilizatoriVizitati.contains(user.getId()))
                  //ca forEach (op term), peek-operatie intermediara
                .peek(user->{
                    List<Utilizator> comunitateC = new ArrayList<>();
                    try {
                        DFS(user.getId(), utilizatoriVizitati, comunitateC);
                    } catch (SQLException e) {
                        throw new RuntimeException(e);
                    }
                })
                .count();
    }

    private List<Utilizator> GetAllUser() throws SQLException {
        List<Utilizator> rez = new ArrayList<>();
        repoUtilizator.findAll().forEach(rez::add);
        return rez;
    }


    public String ComunitateSociabila() throws SQLException {

        List<Long> useriVizitati = new ArrayList<>();

        //variabila atomica - poate fi accesata si modificata de mai multe threaduri
        AtomicInteger max= new AtomicInteger(-1);
        Iterable<Utilizator> all = repoUtilizator.findAll();

        //aici salvez comunitatea sociabila
        AtomicReference<List<Utilizator>> comunitateSociabila = new AtomicReference<>(new ArrayList<>());
        StringBuilder rez = new StringBuilder();

        all.forEach(it->{
            if(!useriVizitati.contains(it.getId())){
                List<Utilizator> comunitateCurenta = new ArrayList<>();
                try {
                    DFS(it.getId(), useriVizitati, comunitateCurenta);
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }

                if (comunitateCurenta.size() > max.get()) {
                    max.set(comunitateCurenta.size());
                    comunitateSociabila.set(comunitateCurenta);
                }
            }
        });

        //construim string-ul pt return
        comunitateSociabila.get().forEach(user-> rez.append(user.getFirstName()).append(" ").append(user.getLastName()).append("  "));

        return rez.toString();

    }


    private List<Prietenie> GetAll() throws SQLException {
        List<Prietenie> rez=new ArrayList<>();
        repoPrietenie.findAll().forEach(rez::add);
        return rez;
    }

    private void DFS(Long userId, List<Long> utilizatoriVizitati, List<Utilizator> comunitateCurenta) throws SQLException {

        utilizatoriVizitati.add(userId);

        Utilizator user = repoUtilizator.findOne(userId).get();
        comunitateCurenta.add(user);

        List<Prietenie> prietenii = GetAll();

        prietenii.stream()
                .filter(prietenie -> prietenie.getId().getLeft().equals(userId)  || prietenie.getId().getRight().equals(userId))
                .forEach(prietenie->
                {Long prietenId = (prietenie.getId().getLeft().equals(userId) ? prietenie.getId().getRight() : prietenie.getId().getLeft());
                    if (!utilizatoriVizitati.contains(prietenId)) {
                        try {
                            DFS(prietenId, utilizatoriVizitati, comunitateCurenta);
                        } catch (SQLException e) {
                            throw new RuntimeException(e);
                        }
                    }
                });
    }


    public void stergeUserPrieteni(Long userID) throws SQLException {

        List<Tuple<Long,Long>> idsToDelete = new ArrayList<>();

        Utilizator user1 = repoUtilizator.findOne(userID).get();
        repoPrietenie.findAll().forEach(prietenie -> {

            if(Objects.equals(prietenie.getId().getLeft(), userID) ||
                    Objects.equals(prietenie.getId().getRight(), userID)) {
                Long prietenID = prietenie.getId().getLeft().equals(userID) ?
                        prietenie.getId().getRight() :
                        prietenie.getId().getLeft();


                Utilizator user2;
                try {
                    user2 = repoUtilizator.findOne(prietenID).get();
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }

                user1.getFriends().remove(user2);
                user2.getFriends().remove(user1);
                idsToDelete.add(prietenie.getId());
                }
        });

        idsToDelete.forEach(repoPrietenie::delete);

    }
}