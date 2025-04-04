package org.example.controller;

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
import org.example.exception.ServiceException;
import org.example.modul.Agent;
import org.example.service.Service;

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
            handleSignUp();
        }
        else if (actionEvent.getSource() == btnCancel) {
            handleCancel();
        }
    }

    private void handleLogIn(){
        String username = txtUsername.getText().trim();
        String password = txtPassword.getText().trim();

        if (username.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please complete all the fields!");
            return;
        }

        try{
            Agent agent = service.searchAgentByUsername(username, password);
            showMainPanel(username, password);
        } catch (ServiceException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    private void showMainPanel(String username, String password){
        try {
            URL resource = getClass().getResource("/views/main-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Home");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            Agent agent = service.searchAgentByUsername(username, password);
            MainController mainController = fxmlLoader.getController();
            mainController.setController(service, dialogStage, agent);

            dialogStage.show();
        }catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    private void handleSignUp() throws IOException {
        try{
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

            stage.close();
            dialogStage.show();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    private void handleCancel(){
        stage.close();
    }
}
