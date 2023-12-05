package com.example.sem7gui.repository.db;

import com.example.sem7gui.domain.User;
import com.example.sem7gui.repository.paging.Page;
import com.example.sem7gui.repository.paging.PageImplementation;
import com.example.sem7gui.repository.paging.Pageable;
import com.example.sem7gui.repository.paging.PagingRepository;

import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class UserDBPagingRepository extends UserDBRepository  implements PagingRepository<Long, User>
{


    public UserDBPagingRepository(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    public Page<User> findAll(Pageable pageable) {
        Stream<User> result = StreamSupport.stream(this.findAll().spliterator(), false)
                .skip(pageable.getPageNumber()  * pageable.getPageSize())
                .limit(pageable.getPageSize());
        return new PageImplementation<>(pageable, result);

    }
}
