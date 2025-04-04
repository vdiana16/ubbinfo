package ui;


import domain.Friendship;
import domain.User;
import service.NetworkService;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * The interface by user
 */
public class Ui {
    private final NetworkService networkService; //the service that manages network operations
    private Scanner scanner;                     // Scanner for reading user input.

    /**
     * Constructor for the Ui class.
     * @param networkService - the service that manages network operations
     */
    public Ui(NetworkService networkService) {
        this.networkService = networkService;
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
        System.out.println("6.Show all friendships");
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
        networkService.addUser(firstName, lastName);
        System.out.println("Utilizator added successfully!");
    }

    /**
     * Gets input for removing a user.
     */
    private void removeUserInput(){
        System.out.println("Enter ID: ");
        Integer id = scanner.nextInt();
        networkService.removeUser(id);
        System.out.println("Utilizator removed successfully!");
    }

    /**
     * Gets input for adding a friendship.
     */
    private void addFriendshipInput(){
        System.out.println("Enter ID1: ");
        Integer id1 = scanner.nextInt();
        String vid = scanner.nextLine();
        System.out.println("Enter ID2: ");
        Integer id2 = scanner.nextInt();
        String vid2 = scanner.nextLine();
        networkService.addFriendship(id1, id2);
        System.out.println("Prietenie added successfully!");
    }

    /**
     * Gets input for removing a friendship.
     */
    private void removeFriendshipInput(){
        System.out.println("Enter ID1: ");
        Integer id1 = scanner.nextInt();
        String vid = scanner.nextLine();
        System.out.println("Enter ID2: ");
        Integer id2 = scanner.nextInt();
        String vid2 = scanner.nextLine();
        networkService.removeFriendship(id1, id2);
        System.out.println("Prietenie removed successfully!");
    }

    /**
     * Displays all users in the network.
     */
    private void showUsersInput(){
        System.out.println("The users are: ");
        Iterable<User> users = networkService.getAllUsers();
        for(User u : users){
            System.out.println(u.toString());
        }
    }

    /**
     * Displays all friendships in the network.
     */
    private void showFriendshipsInput(){
        System.out.println("The friendships are: ");
        Iterable<Friendship> friendships = networkService.getAllFriendships();
        for(Friendship p : friendships){
            System.out.println(p.toString());
        }
    }

    /**
     * Displays the number of communities in the network.
     */
    private void numberOfCommunitiesInput(){
        System.out.println("Number of communities is: ");
        System.out.println(networkService.numberOfCommunities());
    }

    /**
     * Displays the most sociable community in the network.
     */
    private void getMostSociableCommunityInput(){
        System.out.println("Most sociable community is: ");
        ArrayList<User> mostSociableCommunity = networkService.getMostSociableCommunity();
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
