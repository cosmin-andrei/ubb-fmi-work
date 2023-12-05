package ro.ubbcluj.map.socialnetwork.domain.validators;

import ro.ubbcluj.map.socialnetwork.domain.CererePrietenie;

import java.util.Objects;

public class CerereValidator implements Validator<CererePrietenie> {
    @Override
    public void validate(CererePrietenie entity) throws ValidationException {

        Long id1 = entity.getId().getLeft();
        Long id2 = entity.getId().getRight();

        if(id1.equals(id2))
            throw new ValidationException("Id-ul nu poate sa fie acelasi!");
    }
}
