package service;

import domain.Friendship;
import domain.User;
import exceptions.ServiceException;
import repository.file.FriendshipRepository;
import repository.file.UserRepository;

import java.util.ArrayList;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * The class provides services for managing Users entities.
 */
public class UserService implements Service<User>{
    private final UserRepository userRepository;
    private final FriendshipRepository friendshipRepository;

    /**
     * Constructor for the user's service
     * @param userRepository the repository for users
     * @param friendshipRepository the repository for friendships.txt
     */
    public UserService(UserRepository userRepository, FriendshipRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    @Override
    public Long generateID() {
        return StreamSupport.stream(userRepository.findAll().spliterator(), false)
                .mapToLong(User::getId)
                .max()
                .orElse(0L) + 1;
    }

    /**
     * Retrieves all user's friends
     * @param user - whose friends is looking for
     * @return the user's friend list
     */
    public ArrayList<User> getUsersFriends(User user){
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        Long id = user.getId();
        return StreamSupport.stream(friendships.spliterator(),false)
                .filter(friendship -> friendship.getUser1().getId().equals(id) || friendship.getUser2().getId().equals(id))
                .map(friendship -> friendship.getUser1().getId().equals(id) ? friendship.getUser2() : friendship.getUser1())
                .collect(Collectors.toCollection(ArrayList::new));
    }

    /**
     * Retrieves all users from the repository.
     * @return an iterable collection of all User entities
     */
    public Iterable<User> getUsers() {
        return userRepository.findAll();
    }

    /**
     * Adds a new user to the system.
     * @param firstName - user's first name
     * @param lastName - user's last name
     */
    public void addUser(String firstName, String lastName) {
        User user = new User(firstName, lastName);
        user.setId(generateID());
        if(userRepository.save(user).isEmpty()){
            throw new ServiceException("User already exists");
        }
    }

    /**
     * Removes a user from the system based on the user's id
     * @param id - the id of the user to be removed
     */
    public void removeUser(Long id) {
        Optional<User> useropt = userRepository.findOne(id);
        if(useropt.isEmpty()) {
            throw new ServiceException("User not found");
        }
        User user = useropt.get();
        Iterable<Friendship> friendships = friendshipRepository.findAll();

        StreamSupport.stream(friendships.spliterator(),false)
                .filter(friendship -> friendship.getUser1().getId().equals(user.getId()) || friendship.getUser2().getId().equals(user.getId()))
                .forEach(friendship -> friendshipRepository.delete(friendship.getId()));

        userRepository.delete(user.getId());
    }
}