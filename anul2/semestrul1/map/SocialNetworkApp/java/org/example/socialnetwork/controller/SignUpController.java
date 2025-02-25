package org.example.socialnetwork.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.MessageService;
import org.example.socialnetwork.service.SocialNetworkService;

import javafx.scene.control.*;
import java.io.IOException;
import java.net.URL;

public class SignUpController {
    private SocialNetworkService socialNetworkService;
    private MessageService messageService;
    private Stage stage;

    @FXML
    private TextField txtFirstName;

    @FXML
    private TextField txtLastName;

    @FXML
    private TextField txtUsername;

    @FXML
    private PasswordField txtPassword;

    @FXML
    private PasswordField txtConfirmPassword;

    @FXML
    private Button btnSignUp;

    @FXML
    private Button btnCancel;

    public void setSignUp(SocialNetworkService socialNetworkService, MessageService messageService, Stage stage) {
        this.socialNetworkService = socialNetworkService;
        this.messageService = messageService;
        this.stage = stage;
    }

    @FXML
    public void handlePanelClicks(ActionEvent event) throws IOException {
        if (event.getSource() == btnSignUp) {
            handleSignUp();
        } else if (event.getSource() == btnCancel) {
            handleCancel();
        }
    }

    private void handleCancel() {
        showLogInView();
    }

    private void handleSignUp() {
        if (txtFirstName.getText().isEmpty() || txtLastName.getText().isEmpty() ||
                txtUsername.getText().isEmpty() || txtPassword.getText().isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.WARNING, "Warning", "All fields must be filled out!");
            stage.close();
        }
        if(!txtPassword.getText().equals(txtConfirmPassword.getText())) {
            MessageAlert.showMessage(null, Alert.AlertType.WARNING, "Warning", "Password is incorrect!");
            stage.close();
        }
        String firstName = txtFirstName.getText();
        String lastName = txtLastName.getText();
        String username = txtUsername.getText();
        String password = txtPassword.getText();

        User user = socialNetworkService.findUser(username);

        if(user == null) {
            socialNetworkService.addUser(firstName, lastName, username, password);
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Information", "User added successfully!");
        } else {
            MessageAlert.showMessage(null, Alert.AlertType.WARNING, "Information", "User already exists!");
        }
        showLogInView();
    }

    private void showLogInView() {
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/login-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Sign Up");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            LogInController logInController = fxmlLoader.getController();
            logInController.setLogIn(socialNetworkService, messageService, dialogStage);

            stage.close();
            dialogStage.show();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
    }
}
