package org.example.ui;



import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.service.CommunityService;
import org.example.service.FriendshipService;
import org.example.service.UserService;

import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * The interface by user
 */
public class Ui {
    private final UserService userService;
    private final CommunityService communityService;
    private final FriendshipService friendshipService;
    private final Scanner scanner;                     // Scanner for reading user input.

    /**
     * Constructor for the Ui class
     * @param userService for managing Users entities.
     * @param communityService for managing Community.
     * @param friendshipService for managing Friendship entity
     */
    public Ui(UserService userService, CommunityService communityService, FriendshipService friendshipService) {
        this.userService = userService;
        this.communityService = communityService;
        this.friendshipService = friendshipService;
        this.scanner = new Scanner(System.in);
    }

    /**
     * Displays the main menu of the application.
     */
    public void printMenu(){
        System.out.println("1.Add user");
        System.out.println("2.Delete user");
        System.out.println("3.Add friendship");
        System.out.println("4.Delete friendship");
        System.out.println("5.Show all users");
        System.out.println("6.Show all friendships.txt");
        System.out.println("7.Show number of communities");
        System.out.println("8.Show the most sociable community");
    }

    /**
     * Gets input for adding a user.
     */
    private void addUserInput(){
        System.out.println("Enter first name: ");
        String firstName = scanner.nextLine();
        System.out.println("Enter last name: ");
        String lastName = scanner.nextLine();
        userService.addUser(firstName, lastName);
        System.out.println("User added successfully!");
    }

    /**
     * Gets input for removing a user.
     */
    private void removeUserInput(){
        System.out.println("Enter ID: ");
        Long id = scanner.nextLong();
        String vid = scanner.nextLine();
        userService.removeUser(id);
        System.out.println("User removed successfully!");
    }

    /**
     * Gets input for adding a friendship.
     */
    private void addFriendshipInput(){
        System.out.println("Enter ID1: ");
        Long id1 = scanner.nextLong();
        String vid = scanner.nextLine();
        System.out.println("Enter ID2: ");
        Long id2 = scanner.nextLong();
        String vid2 = scanner.nextLine();
        friendshipService.addFriendship(id1, id2);
        System.out.println("Friendship added successfully!");
    }

    /**
     * Gets input for removing a friendship.
     */
    private void removeFriendshipInput(){
        System.out.println("Enter ID1: ");
        Long id1 = scanner.nextLong();
        String vid = scanner.nextLine();
        System.out.println("Enter ID2: ");
        Long id2 = scanner.nextLong();
        String vid2 = scanner.nextLine();
        friendshipService.removeFriendship(id1, id2);
        System.out.println("Friendship removed successfully!");
    }

    /**
     * Displays all users in the network.
     */
    private void showUsersInput(){
        System.out.println("The users are: ");
        Iterable<User> users = userService.getUsers();
        if(!users.iterator().hasNext()){
            System.out.println("No users found!");
        } else {
            StreamSupport.stream(users.spliterator(), false)
                    .forEach(u -> {
                        String friendlist = userService.getUsersFriends(u).stream()
                                .map(fr -> fr.getFirstName() + " " + fr.getLastName())
                                .collect(Collectors.joining(", "));

                        String output = u + (friendlist.isEmpty() ? "No friends" : " Friends= " + friendlist);
                        System.out.println(output);
                    });
        }
    }

    /**
     * Displays all friendships.txt in the network.
     */
    private void showFriendshipsInput() {
        System.out.println("The friendships.txt are: ");
        Iterable<Friendship> friendships = friendshipService.getFriendships();
        if (!friendships.iterator().hasNext()) {
            System.out.println("No friendships found!");
        } else {
            StreamSupport.stream(friendships.spliterator(), false)
                    .forEach(f -> System.out.println(f.toString()));

        }
    }

    /**
     * Displays the number of communities in the network.
     */
    private void numberOfCommunitiesInput(){
        System.out.println("Number of communities is: ");
        System.out.println(communityService.numberOfCommunities());
    }

    /**
     * Displays the most sociable community in the network.
     */
    private void getMostSociableCommunityInput(){
        System.out.println("Most sociable community is: ");
        List<User> mostSociableCommunity = communityService.getMostSociableCommunity();
        mostSociableCommunity.forEach(u-> System.out.println(u.toString()));
    }

    /**
     * Runs the user interface.
     */
    public void runUI(){
        while(true) {
            printMenu();
            System.out.print("Enter your choice: ");
            String command = scanner.nextLine();
            try {
                switch (command) {
                    case "0":
                        System.exit(0);
                    case "1":
                        addUserInput();
                        break;
                    case "2":
                        removeUserInput();
                        break;
                    case "3":
                        addFriendshipInput();
                        break;
                    case "4":
                        removeFriendshipInput();
                        break;
                    case "5":
                        showUsersInput();
                        break;
                    case "6":
                        showFriendshipsInput();
                        break;
                    case "7":
                        numberOfCommunitiesInput();
                        break;
                    case "8":
                        getMostSociableCommunityInput();
                        break;
                    default:
                        System.out.println("Invalid choice!");
                }
            }catch (RuntimeException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}
