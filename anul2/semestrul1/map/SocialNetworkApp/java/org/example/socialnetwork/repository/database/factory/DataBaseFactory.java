package org.example.socialnetwork.repository.database.factory;


import org.example.socialnetwork.domain.validators.Validator;
import org.example.socialnetwork.repository.database.util.AbstractDataBaseRepository;

public interface DataBaseFactory {
    /**
     * Creates Factory for strategy
     * @param strategy that decides type of Validator
     * @return DataBaseFactory conform to strategy
     */
    AbstractDataBaseRepository createRepository (DataBaseRepositoryStrategy strategy, Validator validator);
}