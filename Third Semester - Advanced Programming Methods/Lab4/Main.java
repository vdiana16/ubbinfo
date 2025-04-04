    import domain.validators.*;
import repository.file.FriendshipRepository;
import repository.file.UserRepository;
import service.CommunityService;
import service.FriendshipService;
import service.UserService;
import ui.Ui;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        ValidatorFactory factory = ValidatorFactory.getInstance();
        UserValidator userValidator = (UserValidator) factory.createValidator(ValidatorStrategy.User);
        FriendshipValidator friendshipValidator = (FriendshipValidator) factory.createValidator(ValidatorStrategy.Friendship);

        UserRepository repoFileUser = new UserRepository(userValidator, "./src/data/users.txt");
        FriendshipRepository repoFileFriendship = new FriendshipRepository(friendshipValidator, "./src/data/friendships.txt");

        UserService userService = new UserService(repoFileUser, repoFileFriendship);
        FriendshipService friendshipService = new FriendshipService(repoFileUser, repoFileFriendship);
        CommunityService communityService = new CommunityService(repoFileUser, repoFileFriendship);

        Ui ui = new Ui(userService, communityService, friendshipService);
        ui.runUI();
    }
}
    
