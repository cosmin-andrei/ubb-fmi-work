package com.projects.socialnetwork.repositories;

import com.projects.socialnetwork.models.Entity;
import com.projects.socialnetwork.validators.Validator;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private Map<ID, E> entities;
    private Validator<E> validator;

    public InMemoryRepository(Validator<E> validator) {
        this.entities = new HashMap<>();
        this.validator = validator;
    }


    @Override
    public Optional<E> getById(ID id) {
        if (id == null)
            throw new IllegalArgumentException("ID must not be null!");
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public Iterable<E> getAll() {
        return entities.values();
    }

    @Override
    public Optional<E> save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity must not be null");
        }
        validator.validate(entity);

        return Optional.ofNullable(entities.putIfAbsent(entity.getId(), entity));
    }

    @Override
    public Optional<E> delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID must not be null!");
        }
        return Optional.ofNullable(entities.remove(id));
    }

    @Override
    public Optional<E> update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity must not be null");
        }
        validator.validate(entity);

        return Optional.ofNullable(entities.putIfAbsent(entity.getId(), entity));
    }

}
