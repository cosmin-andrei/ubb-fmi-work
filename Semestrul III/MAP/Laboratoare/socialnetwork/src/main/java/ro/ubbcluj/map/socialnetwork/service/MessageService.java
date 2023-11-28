package ro.ubbcluj.map.socialnetwork.service;

import ro.ubbcluj.map.socialnetwork.domain.Message;
import ro.ubbcluj.map.socialnetwork.domain.validators.ValidationException;
import ro.ubbcluj.map.socialnetwork.repository.MessageRepo;
import ro.ubbcluj.map.socialnetwork.repository.Repository;

public class MessageService {

    private MessageRepo repo;

    public MessageService(MessageRepo repo) {
        this.repo = repo;
    }

//    @Override
//    public boolean addMessage(Message message) {
//        Message msg = null;
//        try{
//            msg = repo.addMsg(message);
//        } catch (Exception e) {
//            throw new RuntimeException(e);
//            return false;
//        }
//
//        if(msg != null){
//            throw new ValidationException("Exista deja acest mesaj");
//        }
//
//        return true;
//    }
}
