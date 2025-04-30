package org.example.client.controller;

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
import org.example.model.Agent;
import org.example.services.ServiceException;
import org.example.services.TravelServices;


import java.io.IOException;
import java.net.URL;


public class LoginController {
    private TravelServices server;
    private Stage stage;
    private Agent loggedAgent;

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

    public void setController(TravelServices server, Stage stage) {
        this.server = server;
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

        try {
            URL resource = getClass().getResource("/views/main-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();
            MainController mainController = fxmlLoader.getController();
            Agent agent = server.login(username, password, mainController);
            if (agent == null) {
                throw new ServiceException("Invalid username or password");
            }
            else {
                Stage dialogStage = new Stage();
                mainController.setController(server, dialogStage, agent);
                dialogStage.setTitle("Home");
                dialogStage.initModality(Modality.WINDOW_MODAL);
                Scene scene = new Scene(root);
                dialogStage.setScene(scene);
                stage.close();
                dialogStage.show();
            }
        }catch (ServiceException | IOException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
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
            signUpController.setController(server, dialogStage);

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
