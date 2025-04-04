package service;

import domain.Friendship;
import domain.User;
import exceptions.ServiceException;
import repository.Repository;

import java.util.*;

/**
 * Service for the network which it manages the network logic
 */

public class NetworkService implements Service<Integer> {
    private final Repository<Integer, User> repoUsers;
    private final Repository<Tuple<Integer,Integer>, Friendship> repoFriendships;

    public NetworkService(Repository<Integer, User> repoUsers, Repository<Tuple<Integer, Integer>, Friendship> repoFriendships) {
        this.repoUsers = repoUsers;
        this.repoFriendships = repoFriendships;
    }

    @Override
    public void addUser(String firstName, String lastName) {
        User user = new User(firstName, lastName);
        repoUsers.save(user);
    }

    @Override
    public User removeUser(Integer id) {
        User user = repoUsers.findOne(id);
        if(user == null) {
            throw new ServiceException("User not found");
        }
        List<User> prieteni = new ArrayList<>(user.getFriends());

        try {
            prieteni.forEach(friend -> removeFriendship(id, friend.getId()));
            prieteni.forEach(friend -> removeFriendship(friend.getId(), id));
        } catch (ServiceException e){

        }
        user.setFriends(new ArrayList<>());
        User deletedutilizator = repoUsers.delete(user.getId());
        return deletedutilizator;
    }

    @Override
    public void addFriendship(Integer id1, Integer id2) {
        Friendship friendship = new Friendship(id1, id2);
        addFriends(id1,id2);
        repoFriendships.save(friendship);
    }

    private void addFriends(Integer id1, Integer id2) {
        User user1 = repoUsers.findOne(id1);
        User user2 = repoUsers.findOne(id2);
        if(user1 == null) {
            throw new ServiceException("User1 not found");
        }
        if(user2 == null) {
            throw new ServiceException("User2 not found");
        }
        ArrayList<User> users1 = new ArrayList<>(user1.getFriends());
        ArrayList<User> users2 = new ArrayList<>(user2.getFriends());

        if(users1.contains(user2)) {
            throw new ServiceException("The friendship already exists");
        }
        if(users2.contains(user1)) {
            throw new ServiceException("The friendship already exists");
        }
        if(id1 == id2){
            throw new ServiceException("The friendship is not possible!");
        }

        users1.add(user2);
        users2.add(user1);

        user1.setFriends(users1);
        user2.setFriends(users2);

        repoUsers.update(user1);
        repoUsers.update(user2);
    }


    @Override
    public boolean removeFriendship(Integer id1, Integer id2) {
        Friendship p = new Friendship(id1, id2);
        Friendship friendship = repoFriendships.findOne(p.getId());
        if(friendship == null) {
            throw new ServiceException("The friendship not found");
        }
        repoFriendships.delete(friendship.getId());
        removeFriends(id1,id2);

        return true;
    }

    private void removeFriends(Integer id1, Integer id2) {
        User user1 = repoUsers.findOne(id1);
        User user2 = repoUsers.findOne(id2);
        ArrayList<User> friends1 = new ArrayList<>(user1.getFriends());
        ArrayList<User> friends2 = new ArrayList<>(user2.getFriends());
        friends1.remove(user2);
        friends2.remove(user1);
        user1.setFriends(friends1);
        user2.setFriends(friends2);
        repoUsers.update(user1);
        repoUsers.update(user2);
    }


    @Override
    public Iterable getAllUsers() {
        return repoUsers.findAll();
    }

    @Override
    public Iterable getAllFriendships() {
        return repoFriendships.findAll();
    }

    private void dfs(User user, Set<User> visited)  {
        visited.add(user);
        for(User friend : user.getFriends()) {
            if(!visit(friend.getId(), visited)) {
                dfs(friend, visited);
            }
        }
    }

    private boolean visit(Integer id, Set<User> visited) {
        for(User i : visited){
            Integer id1 = i.getId();
            if(id1.equals(id)) {
                return true;
            }
        }
        return false;
    }

    public int numberOfCommunities(){
        Set<User> visited = new HashSet<>();
        int countComp = 0;
        Iterable<User> grafRetea = repoUsers.findAll();
        for(User user : grafRetea) {
            if(!visit(user.getId(), visited)) {
                dfs(user, visited);
                countComp++;
            }
        }
        return countComp;
    }

    public ArrayList<User> getMostSociableCommunity() {
        Set<User> visited = new HashSet<>();
        ArrayList<User> mostSociableCommunity = new ArrayList<>();

        int maxPathLength = 0;

        for (User user : repoUsers.findAll()) {
            if (!visited.contains(user)) {
                // Creăm o listă temporară pentru utilizatorii din această comunitate
                ArrayList<User> currentCommunity = new ArrayList<>();
                // Lista pentru a salva drumul maxim
                LinkedList<User> path = new LinkedList<>();

                // Calculăm lungimea drumului maxim în această comunitate
                int currentPathLength = dfsWithPath(user, visited, currentCommunity, path);

                // Verificăm dacă această comunitate are drumul maxim
                if (currentPathLength > maxPathLength) {
                    maxPathLength = currentPathLength;
                    mostSociableCommunity = currentCommunity;
                }
            }
        }

        ArrayList<User> mostSociableCommunity1 = new ArrayList<>();
        for(User u:mostSociableCommunity) {
            mostSociableCommunity1.add(u);
        }
        return mostSociableCommunity1;
    }

    // Metoda DFS pentru a calcula lungimea drumului și a salva comunitatea
    private int dfsWithPath(User user, Set<User> visited, List<User> currentCommunity, LinkedList<User> path) {
        visited.add(user);
        currentCommunity.add(user);
        path.add(user);

        int maxDepth = 0;

        for (User friend : user.getFriends()) {
            if (!visited.contains(friend)) {
                int depth = dfsWithPath(friend, visited, currentCommunity, path) + 1; // +1 pentru fiecare legătură
                maxDepth = Math.max(maxDepth, depth);
            }
        }

        path.removeLast(); // Îndepărtează utilizatorul curent din drumul curent

        return maxDepth;
    }
}
