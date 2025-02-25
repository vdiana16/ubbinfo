package org.example.socialnetwork.repository.database.util;



import org.example.socialnetwork.domain.Entity;
import org.example.socialnetwork.domain.validators.Validator;
import org.example.socialnetwork.repository.Repository;

import java.util.Optional;

public abstract class AbstractDataBaseRepository <ID, E extends Entity<ID>> implements Repository<ID, E> {
    protected Validator<E> validator;
    protected DataBaseAccess dataBaseAccess;
    protected String tableName;

    public AbstractDataBaseRepository(DataBaseAccess dataBaseAccess, String tableName, Validator<E> validator) {
        this.dataBaseAccess = dataBaseAccess;
        this.tableName = "\"" + tableName + "\"";
        this.validator = validator;
    }

    @Override
    public abstract Optional<E> findOne(ID id);

    @Override
    public abstract Iterable<E> findAll();

    @Override
    public abstract Optional<E> save(E entity);

    @Override
    public abstract Optional<E> delete(ID id);

    @Override
    public abstract Optional<E> update(E entity);
}

