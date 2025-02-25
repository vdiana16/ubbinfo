
package service;


import domain.Friendship;
import domain.User;
import repository.memory.InMemoryRepository;

import java.util.*;
import java.util.HashSet;

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
        int communitiesCount = 0;

        for (User user : userRepository.findAll()) {
            if (!visited.contains(user.getId())) {
                communitiesCount++;
                exploreCommunity(user.getId(), visited);
            }
        }

        return communitiesCount;
    }

    private void exploreCommunity(Long userId, Set<Long> visited) {
        visited.add(userId);
        // Get all friendships.txt for the current user
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getUser1().getId().equals(userId) && !visited.contains(friendship.getUser2().getId())) {
                exploreCommunity(friendship.getUser2().getId(), visited);
            } else if (friendship.getUser2().getId().equals(userId) && !visited.contains(friendship.getUser1().getId())) {
                exploreCommunity(friendship.getUser1().getId(), visited);
            }
        }
    }

    /**
     * Retrieves the most sociable community
     * @return an ArrayList of User objects representing the most sociable community
     */
    public ArrayList<User> getMostSociableCommunity(){
        List<List<User>> communities = new ArrayList<>();
        Set<Long> visited = new HashSet<>();

        // Find all communities
        for (User user : userRepository.findAll()) {
            if (!visited.contains(user.getId())) {
                List<User> community = new ArrayList<>();
                exploreCommunityForMostSociable(user.getId(), visited, community);
                communities.add(community);
            }
        }

        // Find the community with the most users
        List<User> mostSociableCommunity = new ArrayList<>();
        int maxFriends = 0;

        for (List<User> community : communities) {
            int totalFriends = 0;
            for (User user : community) {
                totalFriends += countFriends(user);
            }

            if (totalFriends > maxFriends) {
                maxFriends = totalFriends;
                mostSociableCommunity = community;
            }
        }

        return new ArrayList<>(mostSociableCommunity);
    }

    private void exploreCommunityForMostSociable(Long userId, Set<Long> visited, List<User> community) {
        visited.add(userId);
        community.add(userRepository.findOne(userId));

        // Get all friendships.txt for the current user
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getUser1().getId().equals(userId) && !visited.contains(friendship.getUser2().getId())) {
                exploreCommunityForMostSociable(friendship.getUser2().getId(), visited, community);
            } else if (friendship.getUser2().getId().equals(userId) && !visited.contains(friendship.getUser1().getId())) {
                exploreCommunityForMostSociable(friendship.getUser1().getId(), visited, community);
            }
        }
    }

    private int countFriends(User user) {
        int count = 0;
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getUser1().equals(user) || friendship.getUser2().equals(user)) {
                count++;
            }
        }
        return count;
    }


}
