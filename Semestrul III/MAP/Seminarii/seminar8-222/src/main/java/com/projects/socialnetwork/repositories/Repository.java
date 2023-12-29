package com.projects.socialnetwork.repositories;

import com.projects.socialnetwork.models.Entity;

import java.util.Optional;

/**
 * CRUD operations repository interface
 *
 * @param <ID> - type E must have an attribute of type ID
 * @param <E>  -  type of entities saved in repository
 */

public interface Repository<ID, E extends Entity<ID>>  {

    /**
     * gets the entity with the specified id
     *
     * @param id -the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     * or null - if there is no entity with the given id
     * @throws IllegalArgumentException if id is null.
     */
    Optional<E> getById(ID id);

    /**
     * returns all entities
     *
     * @return all entities
     */
    Iterable<E> getAll();

    /**
     * saves the given entity to the repository
     *
     * @param entity entity must be not null
     * @return null- if the given entity is saved
     * otherwise returns the entity (id already exists)
     * @throws IllegalArgumentException if the given entity is null.     *
     */
    Optional<E> save(E entity);


    /**
     * removes the entity with the specified id
     *
     * @param id id must be not null
     * @return the removed entity or null if there is no entity with the given id
     * @throws IllegalArgumentException if the given id is null.
     */
    Optional<E> delete(ID id);

    /**
     * updates the given entity
     *
     * @param entity entity must not be null
     * @return null - if the entity is updated,
     * otherwise  returns the entity  - (e.g. id does not exist).
     * @throws IllegalArgumentException if the given entity is null.
     */
    Optional<E> update(E entity);


}