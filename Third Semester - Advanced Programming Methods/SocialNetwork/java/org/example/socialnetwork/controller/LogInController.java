package org.example.socialnetwork.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.socialnetwork.SocialNetworkApplication;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.MessageService;
import org.example.socialnetwork.service.SocialNetworkService;

import java.io.IOException;
import java.net.URL;

public class LogInController {
    private SocialNetworkService socialNetworkService;
    private MessageService messageService;
    private Stage stage;

    @FXML
    private Label usernameError;

    @FXML
    private Label passwordError;
    
    @FXML
    private TextField txtUsername;

    @FXML
    private PasswordField txtPassword;

    @FXML
    private Button btnLogIn;

    @FXML
    private Button btnSignUp;

    @FXML
    private Button btnCancel;

    public void setLogIn(SocialNetworkService socialNetworkService, MessageService messageService, Stage stage) {
        this.socialNetworkService = socialNetworkService;
        this.messageService = messageService;
        this.stage = stage;
    }

    @FXML
    private void handlePanelClicks(ActionEvent event) throws IOException {
        if(event.getSource() == btnLogIn) {
            handleLogIn();
        }else if(event.getSource() == btnSignUp) {
            handleSignUp();
        }else if (event.getSource() == btnCancel) {
            stage.close();
        }
    }

    private void handleLogIn() throws IOException {
        String username = txtUsername.getText();
        String password = txtPassword.getText();

        if(username.isEmpty() || password.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Autentificare eșuată", "Campurile sunt goale!");
            return;
        }

        User userFound = socialNetworkService.findUser(username);
        if(userFound == null) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Autentificare eșuată", "Utilizatorul nu există!");
            return;
        } else if(userFound.getPassword().equals(password)) {
            try{
                URL resource = getClass().getResource("/org/example/socialnetwork/views/socialnetwork-view.fxml");
                FXMLLoader fxmlLoader = new FXMLLoader(resource);
                AnchorPane root = fxmlLoader.load();

                Stage dialogStage = new Stage();
                dialogStage.setTitle("Home");
                dialogStage.initModality(Modality.WINDOW_MODAL);
                Scene scene = new Scene(root);
                dialogStage.setScene(scene);

                User user = socialNetworkService.findUser(username);
                SocialNetworkController socialNetworkController = fxmlLoader.getController();
                socialNetworkController.setSocialNetworkService(socialNetworkService, messageService, dialogStage, user);

                dialogStage.show();
            }catch (IOException e){
                e.printStackTrace();
                MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Eroare", "A apărut o eroare la încărcarea interfeței!");
                throw new RuntimeException();
            }
        }else if(!userFound.getPassword().equals(password)) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Autentificare eșuată", "Parola introdusă este incorectă!");
            return;
        }
    }

    private void handleSignUp() throws IOException {
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/signup-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Sign Up");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            SignUpController signUpController = fxmlLoader.getController();
            signUpController.setSignUp(socialNetworkService, messageService, dialogStage);

            stage.close();
            dialogStage.show();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
    }
}
