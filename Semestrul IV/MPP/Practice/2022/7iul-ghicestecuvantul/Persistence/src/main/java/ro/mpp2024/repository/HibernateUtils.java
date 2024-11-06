package ro.mpp2024.repository;

import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import ro.mpp2024.model.Configuratie;

public class HibernateUtils {

    private static SessionFactory sessionFactory;

    public static SessionFactory getSessionFactory(){
        if ((sessionFactory==null)||(sessionFactory.isClosed()))
            sessionFactory=createNewSessionFactory();
        return sessionFactory;
    }

    private static  SessionFactory createNewSessionFactory(){
        sessionFactory = new Configuration()
//                .configure("hibernate.properties")
                .addAnnotatedClass(Configuratie.class)
                .buildSessionFactory();
        return sessionFactory;
    }

    public static  void closeSessionFactory(){
        if (sessionFactory!=null)
            sessionFactory.close();
    }
}
