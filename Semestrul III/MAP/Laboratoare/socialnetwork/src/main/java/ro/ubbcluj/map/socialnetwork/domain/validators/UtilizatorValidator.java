package ro.ubbcluj.map.socialnetwork.domain.validators;

import ro.ubbcluj.map.socialnetwork.domain.Utilizator;

public class UtilizatorValidator implements Validator<Utilizator> {
    @Override
    public void validate(Utilizator entity) throws ValidationException {
        if(entity == null){
            throw new ValidationException("Utilizatorul nu poate fi null");
        }

        if(entity.getFirstName().isEmpty()){
            throw new ValidationException("Numele nu poate fi gol");
        }

        if(entity.getLastName().isEmpty()){
            throw new ValidationException("Prenume enu poate fi gol");
        }

    }
}

