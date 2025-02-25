package org.example.socialnetwork.controller;

import javafx.animation.PauseTransition;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.util.Duration;
import org.example.socialnetwork.domain.Friendship;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.MessageService;
import org.example.socialnetwork.service.SocialNetworkService;
import org.example.socialnetwork.utils.events.ChangeEventType;
import org.example.socialnetwork.utils.events.SocialNetworkChangeEvent;
import org.example.socialnetwork.utils.observer.Observer;
import org.example.socialnetwork.utils.paging.Page;
import org.example.socialnetwork.utils.paging.Pageable;

import java.io.IOException;
import java.net.URL;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class SocialNetworkController implements Observer<SocialNetworkChangeEvent> {
    private SocialNetworkService socialNetworkService;
    private MessageService messageService;
    private Stage stage;
    private User currentUser;

    private int currentPage = 0;
    private static final int PAGE_SIZE = 9;

    //StackPane principal
    @FXML
    private StackPane pnlStack;

    @FXML
    private Label pagesLabel;

    @FXML
    private Label lblGreeting;

    @FXML
    private Button btnAddFriend;

    @FXML
    private Button btnDeleteFriend;

    @FXML
    private Button btnFriendsRequests;

    @FXML
    private Button btnBack;

    @FXML
    private Button btnInfo;

    @FXML
    private Button btnMessages;

    @FXML
    private Button btnPrevious;

    @FXML
    private Button btnNext;

    //Friends table
    @FXML
    private TableView<User> tblViewUserFriends;

    @FXML
    private TableColumn<User, String> tblFriendFirstName;

    @FXML
    private TableColumn<User, String> tblFriendLastName;

    @FXML
    private TableColumn<User, String> tblFriendUsername;

    @FXML
    private Label lblNotification;

    @FXML
    public ObservableList<User> modelFriends = FXCollections.observableArrayList();

    public void setSocialNetworkService(SocialNetworkService socialNetworkService, MessageService messageService, Stage stage, User currentUser) {
        this.socialNetworkService = socialNetworkService;
        this.stage = stage;
        this.currentUser = currentUser;
        socialNetworkService.addObserver(this);
        this.messageService = messageService;
        lblGreeting.setText(currentUser.getUsername() + "'s account");

        initModelFriends(currentUser);
    }

    @FXML
    public void initialize() {
        initializeTableFriends();
    }

    private void initializeTableFriends() {
        tblFriendFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tblFriendLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tblFriendUsername.setCellValueFactory(new PropertyValueFactory<>("username"));
        tblViewUserFriends.setItems(modelFriends);
        tblViewUserFriends.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        // Adăugăm un event handler pentru mouse click
        tblViewUserFriends.setOnMouseClicked(event -> {
            // Obținem indexul rândului selectat
            int selectedIndex = tblViewUserFriends.getSelectionModel().getSelectedIndex();

            // Dacă rândul este deja selectat, nu facem nimic (pentru a-l păstra selectat)
            if (selectedIndex != -1) {
                tblViewUserFriends.getSelectionModel().select(selectedIndex);  // Păstrăm selecția
            }
        });
    }

    private void initModelFriends(User user) {
        Page<User> page = socialNetworkService.findAllOnPage(new Pageable(currentPage, PAGE_SIZE), user.getId());

        List<User> friendsList = StreamSupport.stream(page.getElementsOnPage().spliterator(), false)
                .collect(Collectors.toList());
        modelFriends.setAll(friendsList);

        int numberOfPage = (int) Math.ceil((double) page.getTotalNumberOfElements() / PAGE_SIZE);
        pagesLabel.setText("Page " + (currentPage + 1) + " of " + numberOfPage);

        btnPrevious.setDisable(currentPage == 0);
        btnNext.setDisable(currentPage == numberOfPage - 1);
    }

    @FXML
    private void handlePanelClicks(ActionEvent event) {
        if (event.getSource() == btnAddFriend){
            handleAddFriend();
        } else if (event.getSource() == btnDeleteFriend){
            handleDeleteFriend();
        } else if(event.getSource() == btnFriendsRequests){
            handleShowFriendsRequests();
        } else if(event.getSource() == btnMessages){
            handleMessages();
        } else if(event.getSource() == btnInfo){
            handleInfo();
        }
    }

    private void handleInfo() {
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/infouser-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Sign Up");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            InfoUserController infoUserController = fxmlLoader.getController();
            infoUserController.setInfoUserController(socialNetworkService, messageService, currentUser, dialogStage);

            stage.close();
            dialogStage.show();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    private void handleMessages() {
        User selectedFriend = getSelectedFriend();
        if (selectedFriend == null) {
            MessageAlert.showMessage("Input Error", Alert.AlertType.WARNING, "WARNING", "No friend selected!");
            return;
        }
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/message-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Sign Up");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            MessageController messageController = fxmlLoader.getController();
            messageController.setMessageController(socialNetworkService, messageService, dialogStage, currentUser, selectedFriend);

            stage.close();
            dialogStage.show();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    private void handleShowFriendsRequests() {
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/showfriendsrequests-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Friends Requests");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            FriendsRequestsController friendsRequestsController = fxmlLoader.getController();
            friendsRequestsController.setService(socialNetworkService, dialogStage, currentUser);

            dialogStage.showAndWait();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
    }

    private User getSelectedFriend() {
        return tblViewUserFriends.getSelectionModel().getSelectedItem();
    }

    private void handleAddFriend() {
        try{
            URL resource = getClass().getResource("/org/example/socialnetwork/views/addfriend-view.fxml");
            FXMLLoader fxmlLoader = new FXMLLoader(resource);
            AnchorPane root = fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Add Friend");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);
            dialogStage.centerOnScreen();

            AddFriendController addFriendController = fxmlLoader.getController();
            addFriendController.setService(socialNetworkService, dialogStage, currentUser);

            dialogStage.centerOnScreen();
            dialogStage.showAndWait();
        }catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException();
        }
        }

    private void handleDeleteFriend() {
        User selectedFriend = getSelectedFriend();
        if (selectedFriend == null) {
            MessageAlert.showMessage("Input Error", Alert.AlertType.WARNING, "WARNING", "No friend selected!");
            return;
        }
        socialNetworkService.removeFriendship(currentUser.getId(), selectedFriend.getId());
        MessageAlert.showMessage("Success", Alert.AlertType.CONFIRMATION, "INFORMATION","Friend deleted successfully!");
    }

    private void showFriendRequestNotification(User sender) {
        // Arată notificarea (label-ul)
        lblNotification.setText("New friend request from " + sender.getUsername());
        lblNotification.setVisible(true);

        // Ascunde notificarea după câteva secunde (opțional)
        PauseTransition pause = new PauseTransition(Duration.seconds(5));
        pause.setOnFinished(e -> lblNotification.setVisible(false));
        pause.play();
    }

    @Override
    public void update(SocialNetworkChangeEvent event) {
        if (event.getType() == ChangeEventType.ADD && event.getData() instanceof Friendship) {
            Friendship friendship = (Friendship) event.getData();

            // Verifică dacă utilizatorul curent este destinatarul cererii de prietenie
            if (friendship.getUser2().getId().equals(currentUser.getId())) {
                // Afișează notificarea pentru utilizatorul curent
                Platform.runLater(() -> showFriendRequestNotification(friendship.getUser1()));
            }
        }
        initModelFriends(currentUser);
    }

    public void onNextPage(ActionEvent actionEvent){
        currentPage++;
        initModelFriends(currentUser);
    }

    public void onBeforePage(ActionEvent actionEvent){
        currentPage--;
        initModelFriends(currentUser);
    }
}
