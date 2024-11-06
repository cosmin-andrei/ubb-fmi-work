package ro.mpp2024;

import org.hibernate.Session;
import ro.mpp2024.IRepositories.IConfiguratieRepo;
import ro.mpp2024.utils.HibernateUtils;

import java.util.Optional;

public class ConfiguratieRepository implements IConfiguratieRepo {
    @Override
    public Optional<Configuratie> findOne(Long id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return Optional.ofNullable(session.get(Configuratie.class, id));
        }
    }

    @Override
    public Iterable<Configuratie> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Configuratie", Configuratie.class).getResultList();
        }catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Optional<Configuratie> save(Configuratie entity) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();

            Configuratie existingConfiguratie = session.createQuery("from Configuratie where id = :id", Configuratie.class)
                    .setParameter("id", entity.getId())
                    .uniqueResult();
            if (existingConfiguratie != null) {
                return Optional.empty();
            }

            Long id = (Long) session.save(entity);
            session.getTransaction().commit();
            return findOne(id);
        }
    }

    @Override
    public Optional<Configuratie> delete(Long aLong) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            session.beginTransaction();
            Configuratie configuratie = session.get(Configuratie.class, aLong);
            if (configuratie != null) {
                session.delete(configuratie);
            }
            session.getTransaction().commit();
            return Optional.ofNullable(configuratie);
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
    public Integer getSize() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("select count(*) from Configuratie", Long.class).uniqueResult().intValue();
        }
    }
}
