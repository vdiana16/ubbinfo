package repository.file;

import domain.Friendship;
import domain.validators.Validator;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

/**
 * Repository for managing Friendship entities, extending the AbstractFileRepository
 * This class handles the persistence of Friendship data to and from a file.
 */
public class FriendshipRepository extends AbstractFileRepository<Tuple<Integer,Integer>, Friendship> {
    public FriendshipRepository(Validator<Friendship> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public Friendship createEntity(String line) {
        String[] splited = line.split(";");
        Integer id1 = Integer.parseInt(splited[0]);
        Integer id2 = Integer.parseInt(splited[1]);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        LocalDate data = LocalDate.parse(splited[2],formatter);

        Friendship friendship = new Friendship(id1,id2);
        friendship.setId(new Tuple<>(id1, id2));

        return friendship;
    }

    @Override
    public String saveEntity(Friendship entity) {
        Tuple<Integer, Integer> id = entity.getId();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

        return id.getFirst() + ";" + id.getSecond() + ";" + entity.getData().format(formatter);
    }
}