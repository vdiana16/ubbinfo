package org.example.socialnetwork.service;

import org.example.socialnetwork.domain.Friendship;
import org.example.socialnetwork.domain.FriendshipStatus;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.exceptions.ServiceException;
import org.example.socialnetwork.repository.Repository;
import org.example.socialnetwork.repository.database.UserPaging;
import org.example.socialnetwork.utils.events.ChangeEventType;
import org.example.socialnetwork.utils.events.SocialNetworkChangeEvent;
import org.example.socialnetwork.utils.observer.Observable;
import org.example.socialnetwork.utils.observer.Observer;
import org.example.socialnetwork.utils.paging.Page;
import org.example.socialnetwork.utils.paging.Pageable;

import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class SocialNetworkService implements Service<Long>, Observable<SocialNetworkChangeEvent> {
    private final UserPaging userRepository;
    private final Repository<Long, Friendship> friendshipRepository;
    private List<Observer<SocialNetworkChangeEvent>> observers = new ArrayList<>();

    public SocialNetworkService(UserPaging userRepository, Repository<Long, Friendship> friendshipRepository){
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    public Page<User> findAllOnPage(Pageable pageable, Long id) {
        return userRepository.findAllOnPage(pageable, id);
    }

    @Override
    public void addObserver(Observer<SocialNetworkChangeEvent> observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<SocialNetworkChangeEvent> observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(SocialNetworkChangeEvent e) {
        observers.stream().forEach(x -> x.update(e));
    }

    @Override
    public boolean addUser(String firstName, String lastName, String username, String password) {
        User user = new User(firstName, lastName, username, password);
        userRepository.save(user);
        notifyObservers(new SocialNetworkChangeEvent(ChangeEventType.ADD, user));
        return true;
    }

    @Override
    public User removeUser(Long id) {
        Optional<User> useropt = userRepository.findOne(id);
        if(useropt.isEmpty()) {
            throw new ServiceException("User not found");
        }
        User user = useropt.get();
        userRepository.delete(user.getId());
        notifyObservers(new SocialNetworkChangeEvent(ChangeEventType.DELETE, user));
        return user;
    }

    private User findUserByUsername(String username) {
        return (User) StreamSupport.stream(userRepository.findAll().spliterator(), false)
                .filter(user -> user.getUsername().equals(username))
                .findFirst().orElse(null);
    }

    public User findUserById(Long id) {
        Optional<User> useropt = userRepository.findOne(id);
        if (useropt.isEmpty()) {
            throw new ServiceException("User not found");
        } else {
            return useropt.get();
        }
    }

    public boolean updateUser(String firstName, String lastName, String username, String password, String oldusername) {
        User user = findUserByUsername(oldusername);
        User newUser = new User(firstName, lastName, username, password);
        if(user == null){
            throw new ServiceException("User not found");
        }
        newUser.setId(user.getId());
        boolean updated = userRepository.update(newUser).isPresent();
        if(updated){
            notifyObservers(new SocialNetworkChangeEvent(ChangeEventType.UPDATE, newUser));
        }
        return updated;
    }

    public Friendship findFriendship(Long id1, Long id2){
        Iterable<Friendship> frds = friendshipRepository.findAll();
        Optional<Friendship> friendship = StreamSupport.stream(frds.spliterator(), false)
                .filter(f -> (f.getUser1().getId().equals(id1) && f.getUser2().getId().equals(id2)) ||
                        (f.getUser1().getId().equals(id2) && f.getUser2().getId().equals(id1)))
                .findFirst();
        return friendship.orElse(null);
    }

    @Override
    public boolean addFriendship(Long id1, Long id2) {
        Optional<User> user1opt = userRepository.findOne(id1);
        Optional<User> user2opt = userRepository.findOne(id2);

        User user1 = user1opt.orElse(null);
        User user2 = user2opt.orElse(null);
        Friendship friendship = new Friendship(user1, user2, LocalDateTime.now(), FriendshipStatus.PENDING);

        friendshipRepository.save(friendship);
        notifyObservers(new SocialNetworkChangeEvent(ChangeEventType.ADD, friendship));
        return true;
    }

    @Override
    public boolean removeFriendship(Long id1, Long id2) {
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        Optional<Friendship> fr = StreamSupport.stream(friendships.spliterator(), false)
                .filter(friendship -> (friendship.getUser1().getId().equals(id1) && friendship.getUser2().getId().equals(id2))
                        || friendship.getUser1().getId().equals(id2) && friendship.getUser2().getId().equals(id1))
                .findFirst();
        if(fr.isPresent()){
            friendshipRepository.delete(fr.get().getId());
        }
        else{
            throw new ServiceException("Friendship not found");
        }
        notifyObservers(new SocialNetworkChangeEvent(ChangeEventType.DELETE, fr.get()));
        return true;
    }

    public boolean modifyFriendship(Long id1, Long id2, FriendshipStatus status) {
        Friendship fr = findFriendship(id1, id2);
        if(status == FriendshipStatus.ACCEPTED){
            fr.setDate(LocalDateTime.now());
            fr.setStatus(FriendshipStatus.ACCEPTED);
            friendshipRepository.update(fr);
            notifyObservers(new SocialNetworkChangeEvent(ChangeEventType.UPDATE, fr));
        } else if(status == FriendshipStatus.REJECTED) {
            friendshipRepository.delete(fr.getId());
            notifyObservers(new SocialNetworkChangeEvent(ChangeEventType.DELETE, fr));
        }
        return true;
    }

    public User findUser(String username){
        User user = findUserByUsername(username);
        return user;
    }

    @Override
    public Iterable<User> getAllUsers() {
        return userRepository.findAll();
    }

    @Override
    public Iterable<Friendship> getAllFriendships() {
        return friendshipRepository.findAll();
    }

    public List<Friendship> getRequests(String username) {
        // Găsim utilizatorul cu username-ul specificat
        User currentUser = findUserByUsername(username);
        if (currentUser == null) {
            throw new ServiceException("User not found");
        }

        // Obținem toate cererile de prietenie din repository
        Iterable<Friendship> friendships = friendshipRepository.findAll();

        // Filtrăm cererile în care utilizatorul este destinatar (User2) și statusul este ACCEPTED sau PENDING
        return StreamSupport.stream(friendships.spliterator(), false)
                .filter(friendship ->
                        (friendship.getUser2().getId().equals(currentUser.getId()) &&
                                (friendship.getStatus() == FriendshipStatus.PENDING || friendship.getStatus() == FriendshipStatus.ACCEPTED))                 )
                .collect(Collectors.toList());
    }

    /**
     * Retrieves all user's friends
     * @param user - whose friends is looking for
     * @return the user's friend list
     */
    public ArrayList<User> getUsersFriends(User user) {
        Long userId = user.getId();

        // Obținem toate prieteniile utilizatorului din repository (ca Iterable)
        Iterable<Friendship> friendshipsIterable = friendshipRepository.findAll();

        // Convertim Iterable la Stream și filtrăm prieteniile cu status ACCEPTED
        List<User> friendsList = StreamSupport.stream(friendshipsIterable.spliterator(), false)
                .filter(friendship ->
                        (friendship.getUser1().getId().equals(userId) || friendship.getUser2().getId().equals(userId))
                                && friendship.getStatus() == FriendshipStatus.ACCEPTED)
                .map(friendship -> {
                    // Adăugăm prietenul corespunzător în funcție de poziția utilizatorului
                    if (friendship.getUser1().getId().equals(userId)) {
                        return friendship.getUser2();
                    } else {
                        return friendship.getUser1();
                    }
                })
                .collect(Collectors.toList());

        // Convertim lista la ArrayList
        return new ArrayList<>(friendsList);
    }

    private void exploreCommunity(Long userId, Set<Long> visited) {
        visited.add(userId);
        // Get all friendships.txt for the current user
        friendshipRepository.findAll().forEach(friendship -> {
            if (friendship.getUser1().getId().equals(userId) && !visited.contains(friendship.getUser2().getId())) {
                exploreCommunity(friendship.getUser2().getId(), visited);
            } else if (friendship.getUser2().getId().equals(userId) && !visited.contains(friendship.getUser1().getId())) {
                exploreCommunity(friendship.getUser1().getId(), visited);
            }
        });
    }

    @Override
    public int numberOfCommunities() {
        Set<Long> visited = new HashSet<>();
        AtomicInteger communitiesCount = new AtomicInteger(0); // Use AtomicInteger

        userRepository.findAll().forEach(user -> {
            if (!visited.contains(user.getId())) {
                communitiesCount.incrementAndGet(); // Increment the count atomically
                exploreCommunity(user.getId(), visited);
            }
        });

        return communitiesCount.get();
    }

    private int countFriendsInCommunity(List<User> community) {
        return community.stream()
                .mapToInt(this::countFriends)
                .sum();
    }

    private int countFriends(User user) {
        List<Friendship> friendships = new ArrayList<>();
        friendshipRepository.findAll().forEach(friendships::add); // Collecting Iterable to List
        return (int) friendships.stream()
                .filter(friendship -> friendship.getUser1().equals(user) || friendship.getUser2().equals(user))
                .count();
        //sau
        /*
         *return (int) StreamSupport.stream(friendshipRepository.findAll().spliterator(), false)
         *.filter(friendship -> friendship.getUser1().equals(user) || friendship.getUser2().equals(user))
         *.count();
         */
    }

    private void exploreCommunityForMostSociable(Long userId, Set<Long> visited, List<User> community) {
        visited.add(userId);
        Optional<User> useropt = userRepository.findOne(userId);
        useropt.ifPresent(community::add);

        // Get all friendships.txt for the current user
        friendshipRepository.findAll().forEach(friendship -> {
            if (friendship.getUser1().getId().equals(userId) && !visited.contains(friendship.getUser2().getId())) {
                exploreCommunityForMostSociable(friendship.getUser2().getId(), visited, community);
            } else if (friendship.getUser2().getId().equals(userId) && !visited.contains(friendship.getUser1().getId())) {
                exploreCommunityForMostSociable(friendship.getUser1().getId(), visited, community);
            }
        });
    }

    @Override
    public ArrayList<User> getMostSociableCommunity() {
        List<List<User>> communities = new ArrayList<>();
        Set<Long> visited = new HashSet<>();

        // Find all communities
        userRepository.findAll().forEach(user -> {
            if (!visited.contains(user.getId())) {
                List<User> community = new ArrayList<>();
                exploreCommunityForMostSociable(user.getId(), visited, community);
                communities.add(community);
            }
        });

        // Find the community with the most users
        List<User> mostSociableCommunity = communities.stream()
                .max(Comparator.comparingInt(this::countFriendsInCommunity))
                .orElse(new ArrayList<>());

        return new ArrayList<>(mostSociableCommunity);
    }

}
