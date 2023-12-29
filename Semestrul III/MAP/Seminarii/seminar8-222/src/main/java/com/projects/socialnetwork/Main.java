package com.projects.socialnetwork;

import com.projects.socialnetwork.models.User;
import com.projects.socialnetwork.repositories.FriendshipDBRepository;
import com.projects.socialnetwork.repositories.Repository;
import com.projects.socialnetwork.repositories.UserDBPagingRepository;
import com.projects.socialnetwork.repositories.UserDBRepository;
import com.projects.socialnetwork.repositories.paging.Page;
import com.projects.socialnetwork.repositories.paging.Pageable;
import com.projects.socialnetwork.repositories.paging.PageableImplementation;
import com.projects.socialnetwork.repositories.paging.PagingRepository;
import com.projects.socialnetwork.services.NetworkService;
import com.projects.socialnetwork.ui.UI;

import java.util.UUID;


public class Main {
    public static void main(String[] args) {

        //get from env
        String url = "jdbc:postgresql://localhost:5432/social_network";
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        UserDBRepository userDBRepository = new UserDBRepository(url, username, password);
        FriendshipDBRepository friendshipDBRepository = new FriendshipDBRepository(url, username, password);

        NetworkService networkService = new NetworkService(userDBRepository, friendshipDBRepository);

//        networkService.addUser("John", "Andrew", "johnandrew", "ja@ex.com", "123");
//        networkService.addUser("Sarah", "Smith", "sarahsmith", "ss@ex.com", "456");
//        networkService.addUser("Michael", "Johnson", "michaeljohnson", "mj@ex.com", "789");
//        networkService.addUser("Emily", "Davis", "emilydavis", "ed@ex.com", "101112");
//        networkService.addUser("James", "Brown", "jamesbrown", "jb@ex.com", "131415");
//        networkService.addUser("Ava", "Wilson", "avawilson", "aw@ex.com", "161718");
//        networkService.addUser("Daniel", "Martinez", "danielmartinez", "dm@ex.com", "192021");
//        networkService.addUser("Olivia", "Jones", "oliviajones", "oj@ex.com", "222324");
//
//        networkService.createFriendship("johnandrew", "sarahsmith");
//        networkService.createFriendship("johnandrew", "michaeljohnson");
//        networkService.createFriendship("michaeljohnson", "emilydavis");
//        networkService.createFriendship("johnandrew", "emilydavis");
//
//        networkService.createFriendship("jamesbrown", "avawilson");
//        networkService.createFriendship("jamesbrown", "danielmartinez");
//        networkService.createFriendship("oliviajones", "avawilson");

         PagingRepository<UUID,User> userDBPagingRepository = new UserDBPagingRepository(url,username,password);

        Pageable pageable = new PageableImplementation(2,3);
        Page<User> page = userDBPagingRepository.findAll(pageable);
        page.getContent().forEach(System.out::println);
        //        networkService.deleteFriendship("jamesbrown","avawilson");
//        networkService.deleteUser("johnandrew");
//        UI ui = new UI(networkService);
//        ui.run();

    }
}