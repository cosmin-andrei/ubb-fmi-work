package ro.mpp2024.repository;

import org.springframework.stereotype.Component;
import org.hibernate.Session;
import ro.mpp2024.model.Runda;
import ro.mpp2024.repository.interfaces.RundaRepoInterface;

import java.util.List;
import java.util.Optional;


@Component
public class RundaRepo implements RundaRepoInterface {

    @Override
    public Optional<Runda> findOne(Long id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return Optional.ofNullable(session.get(Runda.class, id));
        }
    }

    @Override
    public Iterable<Runda> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Runda", Runda.class).getResultList();
        }catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Optional<Runda> save(Runda entity) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();

            Runda existingEntity = session.createQuery("from Runda where id = :id", Runda.class)
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
    public Optional<Runda> delete(Long id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();
            Runda runda = session.get(Runda.class, id);
            if (runda != null) {
                session.delete(runda);
            }
            session.getTransaction().commit();
            return Optional.ofNullable(runda);
        }
    }

    @Override
    public Optional<Runda> update(Runda entity) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();
            session.update(entity);
            session.getTransaction().commit();
            return Optional.of(entity);
        }
    }

    @Override
    public List<Runda> findByPlayer(String player) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Runda where player = :player", Runda.class)
                    .setParameter("player", player)
                    .getResultList();
        }
    }
}
