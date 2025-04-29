package org.example.travelagencyapplication.controller;

import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.travelagencyapplication.domain.Status;
import org.example.travelagencyapplication.domain.Travel;
import org.example.travelagencyapplication.domain.User;
import org.example.travelagencyapplication.service.Service;
import org.example.travelagencyapplication.service.ServiceException;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class AgentHomeController {
    private Service service;
    private Stage stage;
    private User loggedAgent;

    private static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm dd/MM/yyyy");

    @FXML
    private Label lblWelcome;

    @FXML
    private TabPane mainTabPane;

    @FXML
    private Button btnViewTravels;

    @FXML
    private TableView<Travel> tableViewTrips;
    @FXML
    private TableColumn<Travel, String> tblColumnDestination;
    @FXML
    private TableColumn<Travel, String> tblColumnTransportCompany;
    @FXML
    private TableColumn<Travel, String> tblColumnDepartureDate;
    @FXML
    private TableColumn<Travel, Double> tblColumnPrice;
    @FXML
    private TableColumn<Travel, Integer> tblColumnNumberOfAvailableSeats;

    private ObservableList<Travel> modelTrips;

    private void initializeTabels() {
        tblColumnDestination.setCellValueFactory(new PropertyValueFactory<>("destination"));
        tblColumnTransportCompany.setCellValueFactory(new PropertyValueFactory<>("transportCompany"));
        //tblColumnDepartureDate.setCellValueFactory(new PropertyValueFactory<>("departureDate"));
        tblColumnDepartureDate.setCellValueFactory(cellData -> {
            return new SimpleStringProperty(cellData.getValue().getDepartureDate().format(DATE_TIME_FORMATTER));
        });
        tblColumnPrice.setCellValueFactory(new PropertyValueFactory<>("price"));
        tblColumnNumberOfAvailableSeats.setCellValueFactory(new PropertyValueFactory<>("numberOfAvailableSeats"));

        modelTrips = FXCollections.observableArrayList();

        tableViewTrips.setItems(modelTrips);

        tableViewTrips.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }


    private void loadModelTravels() {
        modelTrips.setAll(service.findAllTravels());
    }

    public void setController(Service service, Stage stage, User admin) {
        this.service = service;
        this.stage = stage;
        this.loggedAgent = admin;

        lblWelcome.setText("Welcome, " + admin.getName() + "!");
        initializeTabels();
    }

    @FXML
    private void handleViewTravels() {
        loadModelTravels();
        mainTabPane.getSelectionModel().select(0);
    }

    @FXML
    private void handleLogout() {
        stage.close();
    }
}
