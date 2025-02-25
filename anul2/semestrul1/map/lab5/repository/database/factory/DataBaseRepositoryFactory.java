package org.example.repository.database.factory;

import org.example.domain.validators.Validator;
import org.example.exceptions.RepositoryException;
import org.example.repository.database.FriendshipDataBaseRepository;
import org.example.repository.database.UserDataBaseRepository;
import org.example.repository.database.util.AbstractDataBaseRepository;
import org.example.repository.database.util.DataBaseAccess;

public class DataBaseRepositoryFactory implements DataBaseFactory{
    private final DataBaseAccess data;

    public DataBaseRepositoryFactory(DataBaseAccess data) {
        this.data = data;
    }

    @Override
    public AbstractDataBaseRepository createRepository(DataBaseRepositoryStrategy strategy, Validator validator) {
        switch (strategy) {
            case User -> {return new UserDataBaseRepository(data, strategy.toString(), validator);}
            case Friendship -> {return new FriendshipDataBaseRepository(data, strategy.toString(), validator);}
            default -> throw new RepositoryException( "Unknown strategy: " + strategy);
        }
    }
}
