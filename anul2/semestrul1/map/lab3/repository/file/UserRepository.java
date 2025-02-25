package repository.file;

import domain.User;
import domain.validators.Validator;
import exceptions.ValidationException;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Repository for managing User entities, extending AbstractFileRepository.
 * This class handle the persistence of User data to and from a file.
 */

public class UserRepository extends AbstractFileRepository<Long, User> {
    public UserRepository(Validator<User> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public User createEntity(String line) {
        String[] splited = line.split(";");
        Long userId = Long.parseLong(splited[0]);
        String firstName = splited[1];
        String lastName = splited[2];
        User user = new User(firstName, lastName);
        user.setId(userId);
        return user;
    }

    @Override
    public String saveEntity(User entity) {
        String s = entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName() + ";";
        return s;
    }
}
