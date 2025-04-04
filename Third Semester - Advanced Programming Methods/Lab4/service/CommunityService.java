package service;

import domain.Friendship;
import domain.User;
import repository.inmemory.InMemoryRepository;

import java.util.*;
import java.util.HashSet;
import java.util.concurrent.atomic.AtomicInteger;

public class CommunityService {
    private final InMemoryRepository<Long, User> userRepository;
    private final InMemoryRepository<Long, Friendship> friendshipRepository;

    /**
     * Constructor for a Community with users and friendships.txt
     * @param userRepository keeps the users data
     * @param friendshipRepository keeps the friendships.txt data
     */
    public CommunityService(InMemoryRepository<Long, User> userRepository, InMemoryRepository<Long, Friendship> friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }
    /**
     * Calculates the number of distinct communities
     * @return the number of distinct communities
     */
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

    /**
     * Retrieves the most sociable community
     * @return an ArrayList of User objects representing the most sociable community
     */
    public ArrayList<User> getMostSociableCommunity(){
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
    
    
}
