package service;

import domain.Friendship;
import domain.User;
import exceptions.ServiceException;
import repository.file.FriendshipRepository;
import repository.file.UserRepository;

import java.util.ArrayList;

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
        Long id = 0L;
        for (Friendship friendship : friendships) {
            if(friendship.getId() > id){
                id = friendship.getId();
            }
        }
        return id + 1;
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
     * @return true if the friendship was successfully added
     *          false, otherwise
     */
    public void addFriendship(Long id1, Long id2) {
        Iterable<Friendship> frds = friendshipRepository.findAll();
        for(Friendship f: frds){
            if(f.getUser1().getId() == id1 && f.getUser2().getId() == id2){
                throw new ServiceException("You are already friend");
            }
            if(f.getUser1().getId() == id2 && f.getUser2().getId() == id1){
                throw new ServiceException("You are already friend");
            }

        }
        if(id1 == id2){
            throw new ServiceException("The friendship is not possible!");
        }

        User user1 = userRepository.findOne(id1);
        User user2 = userRepository.findOne(id2);
        if(user1 == null) {
            throw new ServiceException("User1 not found");
        }
        if(user2 == null) {
            throw new ServiceException("User2 not found");
        }

        Friendship friendship = new Friendship(user1, user2);
        friendship.setId(generateID());

        friendshipRepository.save(friendship);
    }

    /**
     * Removes a friendship between two users identifies by their ids.
     * @param id1 - the id of the first user
     * @param id2 - the id of the second user
     * @return true if the friendship was successfully removed
     *      *          false, otherwise
     */
    public void removeFriendship(Long id1, Long id2) {
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        for (Friendship friend : friendships){
            if(friend.getUser1().getId() == id1 && friend.getUser2().getId() == id2){
                friendshipRepository.delete(friend.getId());
            }
            if(friend.getUser1().getId() == id2 && friend.getUser2().getId() == id1){
                friendshipRepository.delete(friend.getId());
            }
        }
    }
}
