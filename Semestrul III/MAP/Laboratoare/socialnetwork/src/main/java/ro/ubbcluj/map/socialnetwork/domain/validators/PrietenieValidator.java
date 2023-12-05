package ro.ubbcluj.map.socialnetwork.domain.validators;

import ro.ubbcluj.map.socialnetwork.domain.Prietenie;

import java.util.Objects;

public class PrietenieValidator implements Validator<Prietenie>{

    @Override
    public void validate(Prietenie entity) throws ValidationException {
        Long id1 = entity.getId().getLeft();
        Long id2 = entity.getId().getRight();

        if(id1.equals(id2))
            throw new ValidationException("Idul nu poate fi acelasi");

    }
}
