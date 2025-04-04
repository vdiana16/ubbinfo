package org.example.socialnetwork.repository.database;

import org.example.socialnetwork.domain.Entity;
import org.example.socialnetwork.repository.Repository;
import org.example.socialnetwork.utils.paging.Page;
import org.example.socialnetwork.utils.paging.Pageable;

public interface PagingRepository<ID, E extends Entity<ID>> extends Repository<ID, E> {
    Page<E> findAllOnPage(Pageable pageable, Long id);
}
