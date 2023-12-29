package com.projects.socialnetwork.repositories.paging;


import com.projects.socialnetwork.models.Entity;
import com.projects.socialnetwork.repositories.Repository;


public interface PagingRepository<ID,
        E extends Entity<ID>>
        extends Repository<ID, E> {

    Page<E> findAll(Pageable pageable);
}
