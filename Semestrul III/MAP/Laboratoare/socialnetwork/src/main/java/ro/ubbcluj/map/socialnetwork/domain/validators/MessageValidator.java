package ro.ubbcluj.map.socialnetwork.domain.validators;

import ro.ubbcluj.map.socialnetwork.domain.Message;

import java.util.Objects;

public class MessageValidator implements Validator<Message> {
    @Override
    public void validate(Message entity) throws ValidationException {
        if(entity.getText().isEmpty())
            throw new ValidationException("Textul mesajului nu poate fi nul");
    }
}
