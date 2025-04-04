package org.example.socialnetwork.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.MessageService;
import org.example.socialnetwork.service.SocialNetworkService;
import org.example.socialnetwork.utils.ActionType;
import org.example.socialnetwork.utils.events.SocialNetworkChangeEvent;
import org.example.socialnetwork.utils.observer.Observer;

import java.io.IOException;
import java.net.URL;

public class InfoUserController implements Observer<SocialNetworkChangeEvent> {
    private SocialNetworkService socialNetworkService;
    private MessageService messageService;
    private User currentUser;
    private Stage stage;

    @FXML
    private Label lblWelcome;

    @FXML
    private Button btnLogout;

    @FXML
    private Button btnNext;

    @FXML
    private Button btnDeleteAccount;

    @FXML
    private Button btnModifyDetails;

    @FXML
    private Label lblUsername;

    @FXML
    private Label lblFirstName;

    @FXML
    private Label lblLastName;


    public void setInfoUserController(SocialNetworkService socialNetworkService, MessageService messageService, User user, Stage stage) {
        this.socialNetworkService = socialNetworkService;
        this.messageService = messageService;
        this.currentUser = user;
        this.stage = stage;
        this.socialNetworkService.addObserver(this);
        setDetails();
    }

    public void setDetails(){
        User found = socialNetworkService.findUserById(currentUser.getId());
        lblWelcome.setText(found.getUsername() + "'s account'");
        lblUsername.setText(found.getUsername());
        lblFirstName.setText(found.getFirstName());
        lblLastName.setText(found.getLastName());
    }

    @FXML
    public void handlePanelClicks(ActionEvent event) {
        if(event.getSource() == btnLogout){
            handleLogout();
        } else if(event.getSource() == btnNext){
            handleBack();
        } else if(event.getSource() == btnDeleteAccount){
            handleDeleteAccount();
        } else if(event.getSource() == btnModifyDetails){
            handleModifyDetails();
        }
    }


    public void handleLogout() {
        boolean confirmed = MessageAlert.showMessageConfirmation("Confirm Delete", "Are you sure you want to delete this user?");
        if (confirmed) {
            stage.close();
        }
    }

    private void handleBack() {
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/socialnetwork-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Social Network");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            SocialNetworkController socialNetworkController = fxmlLoader.getController();
            socialNetworkController.setSocialNetworkService(socialNetworkService, messageService, dialogStage, currentUser);

            stage.close();
            dialogStage.show();
        }catch (IOException e){
            e.printStackTrace();
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Eroare", "A apărut o eroare la încărcarea interfeței!");
            throw new RuntimeException();
        }
    }

    private void handleDeleteAccount() {
        boolean confirmed = MessageAlert.showMessageConfirmation("Confirm Delete", "Are you sure you want to delete this user?");
        if (confirmed) {
            socialNetworkService.removeUser(currentUser.getId());
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "INFORMATION", "User deleted successfully!");
            stage.close();
        }
    }

    private void handleModifyDetails(){
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/userdatainput-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Modify details");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            UserDataInputController userDataInputController = fxmlLoader.getController();
            userDataInputController.setService(socialNetworkService, dialogStage, ActionType.MODIFY, currentUser);

            dialogStage.show();

            currentUser = socialNetworkService.findUserById(currentUser.getId());
            setDetails();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    @Override
    public void update(SocialNetworkChangeEvent event) {
        setDetails();
    }
}
