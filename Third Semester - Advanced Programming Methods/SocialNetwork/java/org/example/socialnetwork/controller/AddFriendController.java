package org.example.socialnetwork.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import org.example.socialnetwork.domain.Friendship;
import org.example.socialnetwork.domain.FriendshipStatus;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.SocialNetworkService;

import java.io.IOException;
import java.net.URL;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class AddFriendController {
    private SocialNetworkService socialNetworkService;
    private Stage dialogStage;
    private User user;

    @FXML
    private TableView<User> tblUsers;

    @FXML
    private TableColumn<User, String> tblFirstName;

    @FXML
    private TableColumn<User, String> tblLastName;

    @FXML
    private TableColumn<User, String> tblUsername;

    @FXML
    private Button btnAddFriend;

    @FXML
    private Button btnCancel;

    // ObservableList pentru tabel
    private ObservableList<User> modelUsers = FXCollections.observableArrayList();

    public void setService(SocialNetworkService socialNetworkService, Stage dialogStage, User user) {
        this.socialNetworkService = socialNetworkService;
        this.dialogStage = dialogStage;
        this.user = user;
        initializeUserTable();
        initModelUsers();
    }

    private void initializeUserTable() {
        tblFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tblLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tblUsername.setCellValueFactory(new PropertyValueFactory<>("username"));
        tblUsers.setItems(modelUsers);
        tblUsers.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        // Adăugăm un event handler pentru mouse click
        tblUsers.setOnMouseClicked(event -> {
            // Obținem indexul rândului selectat
            int selectedIndex = tblUsers.getSelectionModel().getSelectedIndex();

            // Dacă rândul este deja selectat, nu facem nimic (pentru a-l păstra selectat)
            if (selectedIndex != -1) {
                tblUsers.getSelectionModel().select(selectedIndex);  // Păstrăm selecția
            }
        });
    }

    private void initModelUsers() {
        Iterable<User> users=socialNetworkService.getAllUsers();
        List<User> usersList= StreamSupport.stream(users.spliterator(),false).collect(Collectors.toList());
        modelUsers.setAll(usersList);
    }

    private User getSelectedFriend() {
        return tblUsers.getSelectionModel().getSelectedItem();
    }

    @FXML
    private void handleAddFriend() {
        User selectedUser = getSelectedFriend();
        if (selectedUser == null) {
            MessageAlert.showMessage("Input Error", Alert.AlertType.ERROR, "ERROR", "No user selected.");
            return;
        }
        if(user.getId().equals(selectedUser.getId())) {
            MessageAlert.showMessage("Input Error", Alert.AlertType.ERROR, "ERROR", "Same user selected.");
            return;
        }
        Friendship friendship = socialNetworkService.findFriendship(user.getId(), selectedUser.getId());
        if(friendship == null) {
            socialNetworkService.addFriendship(user.getId(), selectedUser.getId());
            System.out.println("Friendship added for user ID: " + selectedUser.getId());
            MessageAlert.showMessage("Success", Alert.AlertType.INFORMATION, "Successfully", "Friendship added successfully!");
            return;
        }
        if(friendship.getStatus().equals(FriendshipStatus.ACCEPTED.name())){
            MessageAlert.showMessage("Unsuccessful", Alert.AlertType.INFORMATION, "Unsuccessfully", "Friendship already exists!");
            return;
        } else{
            MessageAlert.showMessage("Wait", Alert.AlertType.INFORMATION, "Waiting", "Friend still hasn't accepted this request!");
            return;
        }
    }

    @FXML
    private void handleCancel() {
        this.dialogStage.close();
    }
}