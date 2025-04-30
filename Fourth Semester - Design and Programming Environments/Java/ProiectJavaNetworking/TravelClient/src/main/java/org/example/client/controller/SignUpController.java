package org.example.client.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.example.model.Agent;
import org.example.services.TravelServices;


import java.io.IOException;
import java.util.Optional;

public class SignUpController {
    private TravelServices server;
    private Stage stage;
    private Agent agent;

    @FXML
    private TextField txtName;

    @FXML
    private TextField txtUsername;

    @FXML
    private PasswordField txtPassword;

    @FXML
    private Button btnSignUp;

    @FXML
    private Button btnCancel;

    public void setController(TravelServices service, Stage stage) {
        this.server = service;
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
        if (name.isEmpty() || username.isEmpty() || password.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please complete all the fields!");
            return;
        }
        Agent agent = new Agent(name, username, password);
        try{
            agent = server.addAgent(agent);
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Success", "Agent added successfully!");
        } catch (SecurityException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    private void handleCancel(){
        server.logoutForSignUp(agent);
        stage.close();
    }
}
