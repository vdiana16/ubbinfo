
package repository.file;

import domain.Friendship;
import domain.User;
import domain.validators.Validator;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

/**
 * Repository for managing Friendship entities, extending the AbstractFileRepository
 * This class handles the persistence of Friendship data to and from a file.
 */
public class FriendshipRepository extends AbstractFileRepository<Long, Friendship> {
    public FriendshipRepository(Validator<Friendship> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public Friendship createEntity(String line) {
        String[] splited = line.split(";");
        Long id = Long.parseLong(splited[0]);

        Long id1 = Long.parseLong(splited[1]);
        String firstname1 = splited[2];
        String lastname1 = splited[3];
        User u1 = new User(firstname1, lastname1);
        u1.setId(id1);

        Long id2 = Long.parseLong(splited[4]);
        String firstname2 = splited[5];
        String lastname2 = splited[6];
        User u2 = new User(firstname2, lastname2);
        u2.setId(id2);

        Friendship friendship = new Friendship(u1, u2);
        friendship.setId(id);

        return friendship;
    }

    @Override
    public String saveEntity(Friendship entity) {
        String s = entity.getId() + ";";
        s += entity.getUser1().getId() + ";" + entity.getUser1().getFirstName() + ";" + entity.getUser1().getLastName() + ";";
        s += entity.getUser2().getId() + ";" + entity.getUser2().getFirstName() + ";" + entity.getUser2().getLastName() + ";";
        return s;
    }
}
