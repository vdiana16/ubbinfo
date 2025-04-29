package org.example.travelagencyapplication.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.example.travelagencyapplication.domain.Status;
import org.example.travelagencyapplication.domain.User;
import org.example.travelagencyapplication.service.Service;

import java.io.IOException;

public class SignUpController {
    private Service service;
    private Stage stage;

    @FXML
    private TextField txtName;

    @FXML
    private TextField txtUsername;

    @FXML
    private PasswordField txtPassword;

    @FXML
    private TextField txtAgencyName;

    @FXML
    private TextField txtStatus;

    @FXML
    private Button btnSignUp;

    @FXML
    private Button btnCancel;

    public void setController(Service service, Stage stage) {
        this.service = service;
        this.stage = stage;
    }

    @FXML
    public void handlePanelClicks(ActionEvent actionEvent) throws IOException {
        if (actionEvent.getSource() == btnSignUp) {
            handleSignUp();
        }
        else if (actionEvent.getSource() == btnCancel) {
            handleCancel();
        }
    }

    private void handleSignUp(){
        String name = txtName.getText().trim();
        String username = txtUsername.getText().trim();
        String password = txtPassword.getText().trim();
        String agencyName = txtAgencyName.getText().trim();
        String status = txtStatus.getText().trim();
        if (name.isEmpty() || username.isEmpty() || password.isEmpty() || agencyName.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please complete all the fields!");
            return;
        }
        if (status.isEmpty() || (!status.equals("ADMIN") && !status.equals("AGENT"))) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please select a valid status!");
            return;
        }
        Status statusE = Status.valueOf(status);
        try{
            service.addUser(name, username, password, agencyName, statusE);
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Success", "Agent added successfully!");
            stage.close();
        } catch (SecurityException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    private void handleCancel(){
        stage.close();
    }
}