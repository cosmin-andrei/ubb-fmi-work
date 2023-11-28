package ro.ubbcluj.map.socialnetwork.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}