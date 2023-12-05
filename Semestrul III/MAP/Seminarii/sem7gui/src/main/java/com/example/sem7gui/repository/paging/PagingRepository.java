package com.example.sem7gui.repository.paging;


import com.example.sem7gui.domain.Entity;
import com.example.sem7gui.repository.Repository;

public interface PagingRepository<ID,
        E extends Entity<ID>>
        extends Repository<ID, E> {

    Page<E> findAll(Pageable pageable);
}
