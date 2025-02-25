package ui;


import domain.Friendship;
import domain.User;
import service.CommunityService;
import service.FriendshipService;
import service.UserService;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * The interface by user
 */
public class Ui {
    private final UserService userService;
    private final CommunityService communityService;
    private final FriendshipService friendshipService;
    private Scanner scanner;                     // Scanner for reading user input.

    /**
     * Constructor for the Ui class
     * @param userService
     * @param communityService
     * @param friendshipService
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
        for(User u : users){
            String s = "";
            ArrayList<User> friendships = userService.getUsersFriends(u);
            s += u.toString();
            String f = "";
            for(User fr : friendships){
                f += fr.getFirstName() + " " + fr.getLastName() + ",";
            }
            if(f.isEmpty()){
                s += "No friends";
            }
            else {
                s += " Friends= " + f;
            }
            System.out.println(s);
        }
    }

    /**
     * Displays all friendships.txt in the network.
     */
    private void showFriendshipsInput(){
        System.out.println("The friendships.txt are: ");
        Iterable<Friendship> friendships = friendshipService.getFriendships();
        for(Friendship p : friendships){
            System.out.println(p.toString());
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
        ArrayList<User> mostSociableCommunity = communityService.getMostSociableCommunity();
        for(User u : mostSociableCommunity){
            System.out.println(u.toString());
        }
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
