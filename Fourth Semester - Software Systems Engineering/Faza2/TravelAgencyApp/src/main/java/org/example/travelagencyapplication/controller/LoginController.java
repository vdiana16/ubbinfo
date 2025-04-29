package org.example.travelagencyapplication.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.travelagencyapplication.domain.Status;
import org.example.travelagencyapplication.domain.User;
import org.example.travelagencyapplication.service.Service;
import org.example.travelagencyapplication.service.ServiceException;

import java.io.IOException;
import java.net.URL;

public class LoginController {
    private Service service;
    private Stage stage;

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

    public void setController(Service service, Stage stage) {
        this.service = service;
        this.stage = stage;
    }

    @FXML
    public void handlePanelClicks(ActionEvent actionEvent) throws IOException {
        if (actionEvent.getSource() == btnLogIn) {
            handleLogIn();
        }
        else if (actionEvent.getSource() == btnSignUp) {
            URL resource = getClass().getResource("/views/signup-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Sign Up");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            SignUpController signUpController = fxmlLoader.getController();
            signUpController.setController(service, dialogStage);

            clearFields();
            dialogStage.show();
        }
        else if (actionEvent.getSource() == btnCancel) {
            handleCancel();
        }
    }

    private void handleLogIn(){
        String username = txtUsername.getText().trim();
        String password = txtPassword.getText().trim();

        if (username.isEmpty()) {
            clearFields();
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please complete all the fields!");
            return;
        }

        try{
            User user = service.login(username, password);
            if (user.getStatus() == Status.ADMIN) {
                showAdminPanel(username, password);
            }
            else if (user.getStatus() == Status.AGENT) {
                showAgentPanel(username, password);
            }
            else {
                clearFields();
                MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Your account is blocked!");
                return;
            }
        } catch (ServiceException e) {
            clearFields();
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    private void showAdminPanel(String username, String password){
        try {
            URL resource = getClass().getResource("/views/adminhome-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Home Admin");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            User admin = service.login(username, password);
            AdminHomeController adminHomeController = fxmlLoader.getController();
            adminHomeController.setController(service, dialogStage, admin);

            clearFields();
            dialogStage.show();
        }catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    private void showAgentPanel(String username, String password){
        try {
            URL resource = getClass().getResource("/views/agenthome-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Home Agent");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            User agent = service.login(username, password);
            AgentHomeController agentHomeController = fxmlLoader.getController();
            agentHomeController.setController(service, dialogStage, agent);

            clearFields();
            dialogStage.show();
        }catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    private void handleCancel(){
        stage.close();
    }

    private void clearFields() {
        txtUsername.clear();
        txtPassword.clear();
    }
}