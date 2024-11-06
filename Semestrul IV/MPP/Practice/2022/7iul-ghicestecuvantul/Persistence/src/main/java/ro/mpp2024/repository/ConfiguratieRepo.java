package ro.mpp2024.repository;

import org.hibernate.Session;
import ro.mpp2024.model.Configuratie;
import ro.mpp2024.repository.interfaces.ConfiguratieRepoInterface;

import java.util.Optional;

public class ConfiguratieRepo implements ConfiguratieRepoInterface {

    @Override
    public Optional<Configuratie> findOne(Long id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return Optional.ofNullable(session.get(Configuratie.class, id));
        }
    }

    @Override
    public Iterable<Configuratie> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Configuratie ", Configuratie.class).getResultList();
        }catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Optional<Configuratie> save(Configuratie entity) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();

            Configuratie existingEntity = session.createQuery("from Configuratie where id = :id", Configuratie.class)
                    .setParameter("id", entity.getId())
                    .uniqueResult();
            if (existingEntity != null) {
                return Optional.empty();
            }

            Long id = (Long) session.save(entity);
            session.getTransaction().commit();
            return findOne(id);
        }
    }


    @Override
    public Optional<Configuratie> delete(Long id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();
            Configuratie runda = session.get(Configuratie.class, id);
            if (runda != null) {
                session.delete(runda);
            }
            session.getTransaction().commit();
            return Optional.ofNullable(runda);
        }
    }

    @Override
    public Optional<Configuratie> update(Configuratie entity) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();
            session.update(entity);
            session.getTransaction().commit();
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<Configuratie> findByPlayer(String id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return Optional.ofNullable(session.createQuery("from Configuratie where player = :player", Configuratie.class)
                    .setParameter("player", id)
                    .uniqueResult());
        }
    }
}
