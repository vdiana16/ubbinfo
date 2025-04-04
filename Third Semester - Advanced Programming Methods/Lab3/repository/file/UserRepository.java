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

public class UserRepository extends AbstractFileRepository<Integer, User> {
    public UserRepository(Validator<User> validator, String fileName) {
        super(validator, fileName);
    }

    private ArrayList<User> findFriends(ArrayList<Integer> friendIds) {
        ArrayList<User> friends = new ArrayList<>();
        for (Integer friendId : friendIds) {
            User friend = findOne(friendId);
            if (friend != null) {
                friends.add(friend);
            }
        }
        return friends;
    }

    @Override
    public User createEntity(String line) {
        // Împărțim linia în părți
        String[] splited = line.split(";");

        // Validăm numărul minim de părți
        if (splited.length < 3) {
            throw new ValidationException("Not enough data to create User.");
        }

        // Extragem ID-ul, numele și prenumele
        Integer userId = Integer.parseInt(splited[0]); // Presupunem că formatul este corect
        String firstName = splited[1];
        String lastName = splited[2];

        // Creăm utilizatorul
        User user = new User(firstName, lastName);
        user.setId(userId);

        // Creăm lista pentru ID-urile prietenilor
        ArrayList<Integer> friendIds = new ArrayList<>();

        // Adăugăm ID-urile prietenilor
        for (int i = 3; i < splited.length; i++) {
            if (!splited[i].isEmpty()) {
                Integer friendId = Integer.parseInt(splited[i]); // Presupunem că formatul este corect
                friendIds.add(friendId);
            }
        }

        // Găsim prietenii bazându-ne pe ID-urile obținute
        ArrayList<User> friends = findFriends(friendIds);
        user.setFriends(friends);

        return user;
    }

    @Override
    public String saveEntity(User entity) {
        ArrayList<User> friends = entity.getFriends();
        String friendsString = "";
        for(User u : friends) {
            friendsString += u.getId() + ";";
        }
        String s = entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName() + ";" + friendsString;
        return s;
    }
}
