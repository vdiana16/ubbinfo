package repository.file;

import domain.User;
import domain.validators.Validator;

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
        return entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName() + ";";
    }
}
