package org.example.socialnetwork.controller;

import javafx.application.Application;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.socialnetwork.domain.Friendship;
import org.example.socialnetwork.domain.FriendshipStatus;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.SocialNetworkService;
import org.example.socialnetwork.utils.events.ChangeEventType;
import org.example.socialnetwork.utils.events.SocialNetworkChangeEvent;
import org.example.socialnetwork.utils.observer.Observer;

import java.time.format.DateTimeFormatter;
import java.util.List;

public class FriendsRequestsController implements Observer<SocialNetworkChangeEvent> {
    private SocialNetworkService socialNetworkService;
    private Stage dialogStage;
    private User user;
    private ObservableList<Friendship> modelFriendRequests = FXCollections.observableArrayList();

    @FXML
    private ListView<Friendship> listViewRequests;

    @FXML
    private TableView<Friendship> tableViewRequests;

    @FXML
    private TableColumn<Friendship, String> tblSender;

    @FXML
    private TableColumn<Friendship, String> tblStatus;

    @FXML
    private TableColumn<Friendship, String> tblDate;

    @FXML
    private Button btnUpdateRequest;

    public void setService(SocialNetworkService socialNetworkService, Stage dialogStage, User user) {
        this.socialNetworkService = socialNetworkService;
        this.dialogStage = dialogStage;
        this.user = user;
        this.socialNetworkService.addObserver(this);
        initializeModelFriendRequests();
    }

    private void initializeModelFriendRequests(){
        List<Friendship> requests = socialNetworkService.getRequests(user.getUsername());
        modelFriendRequests.setAll(requests);
        listViewRequests.setItems(modelFriendRequests);
        listViewRequests.setCellFactory(param -> new ListCell<Friendship>() {
            @Override
            protected void updateItem(Friendship item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null) {
                    setText(null);
                } else {
                    // Formatează textul pe care îl afișezi în fiecare element al listei
                    String formattedText = "From: " + item.getUser1().getUsername() + "\n" +
                            "Status: " + item.getStatus() + "\n" +
                            "Date: " + item.getDate().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
                    setText(formattedText);
                }
            }
        });

        // Adăugăm un event handler pentru mouse click
        listViewRequests.setOnMouseClicked(event -> {
            // Verificăm dacă un element a fost selectat
            Friendship selectedRequest = listViewRequests.getSelectionModel().getSelectedItem();
            if (selectedRequest != null) {
                // Poți face ceva cu cererea selectată
            }
        });
    }

    private Friendship getSelectedRequest() {
        return listViewRequests.getSelectionModel().getSelectedItem();
    }

    @FXML
    private void handleUpdateRequest() {
        Friendship friendrequest = getSelectedRequest();
        if (friendrequest == null) {
            MessageAlert.showMessage("Input Error", Alert.AlertType.ERROR, "ERROR", "No user selected.");
            return;
        }

        FriendshipStatus status = showStatusChangeDialog();
        boolean succes = socialNetworkService.modifyFriendship(friendrequest.getUser1().getId(), friendrequest.getUser2().getId(), status);
        if(!succes) {
            MessageAlert.showMessage("Input Error", Alert.AlertType.ERROR, "ERROR", "Something went wrong");
            return;
        }
    }

    private FriendshipStatus showStatusChangeDialog() {
        ChoiceDialog<FriendshipStatus> dialog = new ChoiceDialog<>(FriendshipStatus.ACCEPTED,
                FriendshipStatus.ACCEPTED, FriendshipStatus.REJECTED);
        dialog.setTitle("Modify Friendship Request");
        dialog.setHeaderText("Select the new status:");
        dialog.setContentText("Choose status:");

        return dialog.showAndWait().orElse(null);
    }

    @Override
    public void update(SocialNetworkChangeEvent event) {
        if (event.getType() == ChangeEventType.UPDATE || event.getType() == ChangeEventType.DELETE) {
            initializeModelFriendRequests();
            listViewRequests.refresh();
        }
    }
}


