package service;

import domain.Friendship;
import domain.User;
import exceptions.ServiceException;
import repository.file.FriendshipRepository;
import repository.file.UserRepository;

import java.util.ArrayList;
import java.util.List;

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
        Iterable<User> users = userRepository.findAll();
        Long id = 0L;
        for (User user : users) {
            if(user.getId() > id){
                id = user.getId();
            }
        }
        return id + 1;
    }


    public ArrayList<User> getUsersFriends(User user){
        ArrayList<User> friends = new ArrayList<>();
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        Long id = user.getId();
        for(Friendship friendship : friendships){
            Long id1 = friendship.getUser1().getId();
            Long id2 = friendship.getUser2().getId();
            if(id == id1){
                friends.add(friendship.getUser2());
            }
            if(id == id2){
                friends.add(friendship.getUser1());
            }
        }
        return friends;
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
     * @param firstName
     * @param lastName
     */
    public void addUser(String firstName, String lastName) {
        User user = new User(firstName, lastName);
        user.setId(generateID());
        if(userRepository.save(user) == null){
            throw new ServiceException("User already exists");
        }
    }

    /**
     * Removes a user from the system based on the user's id
     * @param id - the id of the user to be removed
     */
    public void removeUser(Long id) {
        User user = userRepository.findOne(id);
        if(user == null) {
            throw new ServiceException("User not found");
        }

        Iterable<Friendship> friendships = friendshipRepository.findAll();
        for(Friendship friendship : friendships){
            if(friendship.getUser1().getId() == user.getId() || friendship.getUser2().getId() == user.getId()){
                friendshipRepository.delete(friendship.getId());
            }
        }

        userRepository.delete(user.getId());
    }

}
