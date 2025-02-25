package org.example.socialnetwork.controller;

import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.socialnetwork.domain.Message;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.service.MessageService;
import org.example.socialnetwork.service.SocialNetworkService;
import org.example.socialnetwork.utils.events.SocialNetworkChangeEvent;
import org.example.socialnetwork.utils.observer.Observer;

import java.io.IOException;
import java.net.URL;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static java.awt.Color.pink;

public class MessageController implements Observer<SocialNetworkChangeEvent> {
    private SocialNetworkService socialNetworkService;
    private MessageService messageService;
    private Stage stage;
    private User currentUser;
    private User friendSelected;

    @FXML
    private Button btnSendMessage;

    @FXML
    private ListView<Message> chatListView;
    @FXML
    private TextField messageInput;
    @FXML
    private TextField searchField;
    @FXML
    private Label chatLabel;
    @FXML
    private Button btnDeleteMessage;
    @FXML
    private Button btnBack;
    @FXML
    private Button btnEditMessage;
    @FXML
    private Button btnReplyMessage;
    @FXML
    private Button btnMessage;

    @FXML
    private ObservableList<Message> modelMessages = FXCollections.observableArrayList();


    public void setMessageController(SocialNetworkService socialNetworkService, MessageService messageService, Stage stage, User currentUser, User friendSelected) {
        this.socialNetworkService = socialNetworkService;
        this.socialNetworkService.addObserver(this);
        this.messageService = messageService;
        this.messageService.addObserver(this);
        this.stage = stage;
        this.currentUser = currentUser;
        this.friendSelected = friendSelected;
        initializeMessages(currentUser, friendSelected);
        initModelMessages(currentUser, friendSelected);
    }

    private void initModelMessages(User u1, User u2) {
        Iterable<Message> messages;
        if (u1 == null || u2 == null) {
            messages = messageService.getAllMessages();
        } else {
            messages = messageService.getMessagesBetweenUsers(u1, u2);
        }
        List<Message> messageList = StreamSupport.stream(messages.spliterator(), false)
                .collect(Collectors.toList());
        modelMessages.setAll(messageList);
    }

    public void handleMessageItemClick(MouseEvent event) {
        if (event.getClickCount() == 1) {
            Message selectedItem = chatListView.getSelectionModel().getSelectedItem();
            if (selectedItem != null) {
                int selectedIndex = chatListView.getSelectionModel().getSelectedIndex();
                boolean alreadySelected = chatListView.getSelectionModel().isSelected(selectedIndex);
                if (alreadySelected) {
                    chatListView.getSelectionModel().clearSelection();
                }
            }
        }
    }

    private void handleSendMessage(User friendSelected) {
        String message = messageInput.getText();
        if (message.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Message cannot be empty!");
        } else {
            messageService.sendMessage(currentUser, friendSelected, message, -1L);
            //sort the messages by date
            modelMessages.sort((o1, o2) -> o1.getDate().compareTo(o2.getDate()));
            messageInput.clear();
        }
    }

    private Message getSelectedMessage() {
        Message selected = chatListView.getSelectionModel().getSelectedItem();
        return selected;
    }


    private void handleReplyMessage() {
        Message selectedMessage = getSelectedMessage();
        String message = messageInput.getText();
        if (message.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Message cannot be empty!");
        } else {
            messageService.sendMessage(currentUser, selectedMessage.getFrom(), message, selectedMessage.getId());
            //sort the messages by date
            modelMessages.sort((o1, o2) -> o1.getDate().compareTo(o2.getDate()));
        }
    }

    @FXML
    private void handleUserPanelClick(ActionEvent event) {
        if (event.getSource() == btnSendMessage) {
            handleSendMessage(friendSelected);
        } else if (event.getSource() == btnDeleteMessage) {
            if (getSelectedMessage() != null) {
                messageService.deleteMessage(getSelectedMessage());
            } else {
                MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "No message selected!");
            }
        } else if (event.getSource() == btnReplyMessage) {
            if (getSelectedMessage() == null || messageInput.getText().isEmpty()) {
                MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "No message selected or message is empty!");
            } else {
                handleReplyMessage();
            }
        } else if(event.getSource() == btnBack){
            handleBack();
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
            throw new RuntimeException();
        }
    }

    private void initializeMessages(User user1, User user2) {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm");
        modelMessages.setAll(messageService.getMessagesBetweenUsers(user1, user2));
        chatLabel.setText("Chat with " + user2.getUsername());

        BackgroundImage backgroundImage = new BackgroundImage(
                new Image("org/example/socialnetwork/images/background.png"),
                BackgroundRepeat.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                new BackgroundSize(
                        BackgroundSize.DEFAULT.getWidth(),
                        BackgroundSize.DEFAULT.getHeight(),
                        true, true, false, false
                )
        );

        Background background = new Background(backgroundImage);
        chatListView.setBackground(background);
        chatListView.setStyle("-fx-background-color: transparent;");
        chatListView.setCellFactory(param -> new ListCell<Message>() {
            @Override
            protected void updateItem(Message message, boolean empty) {
                super.updateItem(message, empty);
                setBackground(Background.EMPTY);
                if (empty || message == null) {
                    setText(null);
                    setGraphic(null);
                } else {
                    // Create components for the message
                    Label messageLabel = new Label(message.getMessage());
                    messageLabel.setWrapText(true);
                    messageLabel.setMaxWidth(170);
                    messageLabel.setStyle("-fx-font-size: 14px;");

                    Label dateLabel = new Label(message.getDate().format(formatter));
                    dateLabel.setStyle("-fx-text-fill: #cccccc; -fx-font-size: 10px;");
                    dateLabel.setAlignment(Pos.CENTER_RIGHT);

                    VBox messageVBox = new VBox(messageLabel, dateLabel);
                    messageVBox.setSpacing(2);
                    messageVBox.setAlignment(Pos.CENTER_RIGHT);
                    messageVBox.setStyle("-fx-background-radius: 10; -fx-padding: 5 10 5 10;");

                    // Check if the message is a reply
                    if (message.getReplyingTo() != -1) {
                        // Retrieve the original message using the replyingTo ID
                        Message originalMessage = messageService.getAllMessages().stream()
                                .filter(x -> x.getId().equals(message.getReplyingTo()))
                                .findFirst()
                                .orElse(null);

                        if (originalMessage != null) {
                            Label originalMessageLabel = new Label(originalMessage.getMessage());
                            originalMessageLabel.setWrapText(true);
                            originalMessageLabel.setMaxWidth(150);
                            originalMessageLabel.setStyle("-fx-font-size: 12px;");

                            Label originalSenderLabel = new Label("Reply to " + originalMessage.getFrom().getUsername());
                            originalSenderLabel.setStyle("-fx-font-size: 10px;");

                            VBox replyVBox = new VBox(originalSenderLabel, originalMessageLabel);
                            if (message.getFrom().equals(currentUser)) {
                                replyVBox.setStyle("-fx-background-color: #f8cbdb; -fx-background-radius: 8; -fx-padding: 5 10 5 10;");
                            } else {
                                replyVBox.setStyle("-fx-background-color: #ff5a98; -fx-background-radius: 8; -fx-padding: 5 10 5 10;");
                            }
                            replyVBox.setSpacing(2);
                            replyVBox.setAlignment(Pos.CENTER_LEFT);

                            // Add a border to visually separate the reply box
                            replyVBox.setStyle(replyVBox.getStyle() + "-fx-border-color: #bbbbbb; -fx-border-width: 1; -fx-border-radius: 8;");

                            messageVBox.getChildren().add(0, replyVBox); // Prepend the reply VBox to the message VBox
                        }
                    }

                    if (message.getFrom().equals(currentUser)) {
                        messageVBox.setStyle(messageVBox.getStyle() + "-fx-background-color: #ff5a98; -fx-text-fill: #FFFFFF;");
                    } else {
                        messageVBox.setStyle(messageVBox.getStyle() + "-fx-background-color: #f8cbdb; -fx-text-fill: #FFFFFF;");
                    }

                    HBox hbox = new HBox(messageVBox);
                    hbox.setSpacing(10);
                    hbox.setAlignment(message.getFrom().equals(currentUser) ? Pos.CENTER_RIGHT : Pos.CENTER_LEFT);

                    setGraphic(hbox);
                }
            }
        });

        chatListView.setItems(modelMessages);
    }

    @Override
    public void update(SocialNetworkChangeEvent event) {
        initializeMessages(currentUser, friendSelected);
    }

}
