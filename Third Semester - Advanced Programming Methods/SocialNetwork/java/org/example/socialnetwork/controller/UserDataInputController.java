package org.example.socialnetwork.controller;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.SocialNetworkService;
import org.example.socialnetwork.utils.ActionType;

import java.io.IOException;

public class UserDataInputController {
    private SocialNetworkService socialNetworkService;
    private Stage dialogStage;
    private ActionType actionType;
    private User user;

    @FXML
    private TextField txtFirstName;

    @FXML
    private TextField txtLastName;

    @FXML
    private TextField txtUsername;

    @FXML
    private PasswordField txtPassword;

    @FXML
    private Button btnModify;

    @FXML
    private Button btnCancel;

    public void setService(SocialNetworkService socialNetworkService, Stage dialogStage, ActionType actionType, User user) {
        this.socialNetworkService = socialNetworkService;
        this.dialogStage = dialogStage;
        this.actionType = actionType;
        this.user = user;
    }

    @FXML
    private void handleModify() throws IOException {
        // Verificăm că toate câmpurile sunt completate
        if (txtFirstName.getText().isEmpty() || txtLastName.getText().isEmpty() || txtUsername.getText().isEmpty() ||
            txtPassword.getText().isEmpty()) {
            MessageAlert.showMessage("Input Error", Alert.AlertType.WARNING, "Warning", "All fields must be filled out!");
            return;
        }

        String firstName = txtFirstName.getText();
        String lastName = txtLastName.getText();
        String username = txtUsername.getText();
        String password = txtPassword.getText();

        if(actionType == ActionType.MODIFY){
            socialNetworkService.updateUser(firstName, lastName, username, password, user.getUsername());
            MessageAlert.showMessage("Success", Alert.AlertType.INFORMATION, "Information", "User added successfully!");
        }
        dialogStage.close(); // Închidem fereastra după salvare
    }

    @FXML
    private void handleCancel() {
        dialogStage.close(); // Închidem fereastra fără a salva
    }
}

