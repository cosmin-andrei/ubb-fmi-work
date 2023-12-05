package ro.ubbcluj.map.socialnetwork.service;

import ro.ubbcluj.map.socialnetwork.domain.Message;
import ro.ubbcluj.map.socialnetwork.domain.Tuple;
import ro.ubbcluj.map.socialnetwork.domain.validators.ValidationException;
import ro.ubbcluj.map.socialnetwork.repository.MessageDBRepository;
import ro.ubbcluj.map.socialnetwork.repository.PrietenieDBRepository;

import java.util.ArrayList;
import java.util.List;

public class MessageService {

    private MessageDBRepository repo;
    private PrietenieDBRepository prietenieDBRepository;

    public MessageService(MessageDBRepository repo, PrietenieDBRepository prietenieDBRepository) {
        this.repo = repo;
        this.prietenieDBRepository = prietenieDBRepository;
    }

    public void addMessage(Message message) {
        if(prietenieDBRepository.findOne(new Tuple<>(message.getIdReceiver(), message.getIdSender())).isEmpty()
        && prietenieDBRepository.findOne((new Tuple<>(message.getIdSender(), message.getIdReceiver()))).isEmpty()) {
            throw new ValidationException("Nu esti prieten cu " + message.getIdReceiver() + " deci nu ii poti trimite mesaje!");
        }

        repo.save(message);
    }

//    public void addReply(Long id, Message message)
//    {
//        message.getReply().add(id);
//        repo.update(message);
//    }

    public List<Message> conversation(Long id1, Long id2) {
        List<Message> allMessages = (List<Message>) getAll();
        List<Message> conversationMessages = new ArrayList<>();

        for (Message message : allMessages) {
            if (isPartOfConversation(message, id1, id2)) {
                conversationMessages.add(message);
            }
        }

        return conversationMessages;
    }

    private boolean isPartOfConversation(Message message, Long id1, Long id2) {
        // Check if the message is between id1 and id2
        return (message.getIdSender().equals(id1) && message.getIdReceiver().equals(id2)) ||
                (message.getIdSender().equals(id2) && message.getIdReceiver().equals(id1));
    }



    private Iterable<Message> getAll()
    {
        return repo.findAll();
    }
}
