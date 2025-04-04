package org.example.socialnetwork.repository.database.factory;


import org.example.socialnetwork.domain.validators.Validator;
import org.example.socialnetwork.exceptions.RepositoryException;
import org.example.socialnetwork.repository.database.FriendshipDataBaseRepository;
import org.example.socialnetwork.repository.database.UserDataBaseRepository;
import org.example.socialnetwork.repository.database.MessageDataBaseRepository;
import org.example.socialnetwork.repository.database.util.AbstractDataBaseRepository;
import org.example.socialnetwork.repository.database.util.DataBaseAccess;

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
            case Message -> {return new MessageDataBaseRepository(data, strategy.toString(), null);}
            default -> throw new RepositoryException( "Unknown strategy: " + strategy);
        }
    }
}

