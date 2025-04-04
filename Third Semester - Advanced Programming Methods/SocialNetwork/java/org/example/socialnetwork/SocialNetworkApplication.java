package org.example.socialnetwork;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.example.socialnetwork.controller.LogInController;
import org.example.socialnetwork.domain.*;
import org.example.socialnetwork.domain.validators.Validator;
import org.example.socialnetwork.domain.validators.ValidatorFactory;
import org.example.socialnetwork.domain.validators.ValidatorStrategy;
import org.example.socialnetwork.repository.database.UserPaging;
import org.example.socialnetwork.repository.database.factory.DataBaseRepositoryFactory;
import org.example.socialnetwork.repository.database.factory.DataBaseRepositoryStrategy;
import org.example.socialnetwork.repository.database.util.AbstractDataBaseRepository;
import org.example.socialnetwork.repository.database.util.DataBaseAccess;
import org.example.socialnetwork.service.MessageService;
import org.example.socialnetwork.service.SocialNetworkService;

import java.io.IOException;
import java.sql.SQLException;

public class SocialNetworkApplication extends Application {
    private DataBaseAccess dataAccess;
    private AbstractDataBaseRepository<Long, User> userRepository;
    private AbstractDataBaseRepository<Long, Friendship> friendRepository;
    private AbstractDataBaseRepository<Long, Message> messageRepository;
    public SocialNetworkService socialNetworkService;
    public MessageService messageService;

    @Override
    public void start(Stage primaryStage) throws Exception {
        String url = "jdbc:postgresql://localhost:5432/postgres";
        String user = "socialnet";
        String password = "1234";

        ValidatorFactory validatorFactory = ValidatorFactory.getInstance();
        Validator userValidator = validatorFactory.createValidator(ValidatorStrategy.User);
        Validator friendshipValidator = validatorFactory.createValidator(ValidatorStrategy.Friendship);

        this.dataAccess = new DataBaseAccess(url, user, password);
        try{
            dataAccess.createConnection();
        }catch (SQLException e){
            throw new RuntimeException(e);
        }

        DataBaseRepositoryFactory repoFactory = new DataBaseRepositoryFactory(dataAccess);
        this.userRepository = repoFactory.createRepository(DataBaseRepositoryStrategy.User, userValidator);
        this.friendRepository = repoFactory.createRepository(DataBaseRepositoryStrategy.Friendship, friendshipValidator);
        this.messageRepository = repoFactory.createRepository(DataBaseRepositoryStrategy.Message, null);
        this.socialNetworkService = new SocialNetworkService((UserPaging) userRepository, friendRepository);
        this.messageService = new MessageService(userRepository, friendRepository, messageRepository);
        initView(primaryStage);
        primaryStage.show();
    }

    private void initView(Stage primaryStage) throws IOException {
        FXMLLoader stageLoader = new FXMLLoader();
        stageLoader.setLocation(getClass().getResource("/org/example/socialnetwork/views/login-view.fxml"));
        AnchorPane setLayout = stageLoader.load();
        primaryStage.setTitle("Social Network");
        primaryStage.setScene(new Scene(setLayout, Color.POWDERBLUE));

        LogInController logInController = stageLoader.getController();
        logInController.setLogIn(socialNetworkService, messageService, primaryStage);
    }

    public static void main(String[] args){
       launch(args);
    }
}
