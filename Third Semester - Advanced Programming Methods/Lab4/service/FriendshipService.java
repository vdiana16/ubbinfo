package service;

import domain.Friendship;
import domain.User;
import exceptions.ServiceException;
import repository.file.FriendshipRepository;
import repository.file.UserRepository;

import java.util.Objects;
import java.util.Optional;
import java.util.stream.StreamSupport;

/**
 * The class provides services for managing Friendships entities.
 */
public class FriendshipService implements Service<Friendship>{
    private final UserRepository userRepository;
    private final FriendshipRepository friendshipRepository;

    public FriendshipService(UserRepository userRepository, FriendshipRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    @Override
    public Long generateID() {
        Iterable<Friendship> friendships = friendshipRepository.findAll();

        //folosesc StreamSuport pentru a crea un stream dintr-un Iterable, deoarece metoda stream este disponibila
        //doar pentru colectiile care implementeaza interfata Colllection
        return StreamSupport.stream(friendships.spliterator(), false)
                .mapToLong(Friendship::getId)     // Extrage ID-ul fiecărui Friendship
                .max()                            // Găsește ID-ul maxim
                .orElse(0L) + 1;            // Dacă nu există elemente, folosește 0
    }

    /**
     * Retrieves all friendships.txt in the system.
     * @return an iterable collection of all Friendship objects
     */
    public Iterable<Friendship> getFriendships(){
        return friendshipRepository.findAll();
    }

    /**
     * Add a friendships.txt between two users identified by their ids.
     * @param id1 - the id of the first user
     * @param id2 - the id of the second user
     */
    public void addFriendship(Long id1, Long id2) {
        Iterable<Friendship> frds = friendshipRepository.findAll();
        boolean friendshipExist = StreamSupport.stream(frds.spliterator(), false)
                .anyMatch(f -> (f.getUser1().getId().equals(id1) && f.getUser2().getId().equals(id2)) ||
                        (f.getUser1().getId().equals(id2) && f.getUser2().getId().equals(id1)));
        if(friendshipExist){
            throw new ServiceException("You are already friend");
        }

        if(Objects.equals(id1, id2)){
            throw new ServiceException("The friendship is not possible!");
        }

        Optional<User> user1opt = userRepository.findOne(id1);
        Optional<User> user2opt = userRepository.findOne(id2);
        if(user1opt.isEmpty()){
            throw new ServiceException("User1 not found");
        }
        if(user2opt.isEmpty()) {
            throw new ServiceException("User2 not found");
        }

        User user1 = user1opt.get();
        User user2 = user2opt.get();
        Friendship friendship = new Friendship(user1, user2);
        friendship.setId(generateID());

        friendshipRepository.save(friendship);
    }

    /**
     * Removes a friendship between two users identifies by their ids.
     * @param id1 - the id of the first user
     * @param id2 - the id of the second user
     */
    public void removeFriendship(Long id1, Long id2) {
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        Optional<Friendship> fr = StreamSupport.stream(friendships.spliterator(), false)
                .filter(friendship -> (friendship.getUser1().getId().equals(id1) && friendship.getUser2().getId().equals(id2))
                        || friendship.getUser1().getId().equals(id2) && friendship.getUser2().getId().equals(id1))
                .findFirst();
        fr.ifPresent(friendship -> friendshipRepository.delete(friendship.getId()));

    }
}
