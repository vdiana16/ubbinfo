    import domain.Friendship;
import domain.User;
import domain.validators.*;
import repository.Repository;
import repository.file.FriendshipRepository;
import repository.file.UserRepository;
import repository.memory.InMemoryRepository;
import service.NetworkService;
import ui.Ui;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        ValidatorFactory factory = ValidatorFactory.getInstance();
        UserValidator userValidator = (UserValidator) factory.createValidator(ValidatorStrategy.User);
        FriendshipValidator friendshipValidator = (FriendshipValidator) factory.createValidator(ValidatorStrategy.Friendship);

        Repository<Integer, User> repoUtilizator = new InMemoryRepository<Integer, User>(userValidator);
        Repository<Integer, User> repoFileUtilizator = new UserRepository(userValidator, "./src/data/users.txt");

        Repository<Tuple<Integer, Integer>, Friendship> repoPrietenie = new InMemoryRepository<Tuple<Integer, Integer>, Friendship>(friendshipValidator);
        Repository<Tuple<Integer, Integer>, Friendship> repoFilePrietenie = new FriendshipRepository(friendshipValidator, "./src/data/friendships.txt");

        NetworkService networkService = new NetworkService(repoFileUtilizator, repoFilePrietenie);

        Ui ui = new Ui(networkService);
        ui.runUI();
    }
}
    
