package org.example.socialnetwork.repository.database;

import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.utils.paging.Page;
import org.example.socialnetwork.utils.paging.Pageable;

public interface UserPaging extends PagingRepository<Long, User>{
    Page<User> findAllOnPage(Pageable pageable, Long id);
}
