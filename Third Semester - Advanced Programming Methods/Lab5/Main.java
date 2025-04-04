    package org.example;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.domain.validators.FriendshipValidator;
import org.example.domain.validators.UserValidator;
import org.example.domain.validators.ValidatorFactory;
import org.example.domain.validators.ValidatorStrategy;
import org.example.repository.database.util.AbstractDataBaseRepository;
import org.example.repository.database.util.DataBaseAccess;
import org.example.repository.database.factory.DataBaseRepositoryFactory;
import org.example.repository.database.factory.DataBaseRepositoryStrategy;
import org.example.service.CommunityService;
import org.example.service.FriendshipService;
import org.example.service.UserService;
import org.example.ui.Ui;

public class Main {
    public static void main(String[] args) {
        Properties properties = new Properties();
        try (FileInputStream fis = new FileInputStream("config.properties")) {
            properties.load(fis);
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        String url = properties.getProperty("db.url");
        String user = properties.getProperty("db.username");
        String password = properties.getProperty("db.password");


        ValidatorFactory factory = ValidatorFactory.getInstance();
        UserValidator userValidator = (UserValidator) factory.createValidator(ValidatorStrategy.User);
        FriendshipValidator friendshipValidator = (FriendshipValidator) factory.createValidator(ValidatorStrategy.Friendship);

        DataBaseAccess dataBaseAccess = new DataBaseAccess(url, user, password);
        try{
            dataBaseAccess.createConnection();
        }catch(Exception e){
            throw new RuntimeException(e);
        }

        DataBaseRepositoryFactory repoFactory = new DataBaseRepositoryFactory(dataBaseAccess);
        AbstractDataBaseRepository<Long, User> repoDBUser = repoFactory.createRepository(DataBaseRepositoryStrategy.User, userValidator);
        AbstractDataBaseRepository<Long, Friendship> repoDBFriendship = repoFactory.createRepository(DataBaseRepositoryStrategy.Friendship, friendshipValidator);

        UserService userService = new UserService(repoDBUser, repoDBFriendship);
        FriendshipService friendshipService =  new FriendshipService(repoDBUser, repoDBFriendship);
        CommunityService communityService = new CommunityService(repoDBUser, repoDBFriendship);

        Ui ui = new Ui(userService, communityService, friendshipService);
        ui.runUI();
    }
}
    
