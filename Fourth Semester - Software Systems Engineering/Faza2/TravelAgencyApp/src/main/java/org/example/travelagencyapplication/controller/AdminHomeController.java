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

public class AdminHomeController {
    private Service service;
    private Stage stage;
    private User loggedAdmin;

    private static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm dd/MM/yyyy");

    @FXML
    private TabPane mainTabPane;

    @FXML
    private Label lblWelcome;

    @FXML
    private TextField txtDestination;

    @FXML
    private DatePicker dtpDataDeparture;

    @FXML
    private TextField txtTimeDeparture;

    @FXML
    private TextField txtTransportCompany;

    @FXML
    private TextField txtNumberOfAvailableSeats;

    @FXML
    private TextField txtPrice;

    @FXML
    private TextField txtName;

    @FXML
    private TextField txtUsername;

    @FXML
    private PasswordField txtPassword;


    @FXML
    private Button btnAddTravel;

    @FXML
    private Button btnViewTravels;

    @FXML
    private Button btnAddAgent;

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
        this.loggedAdmin = admin;

        lblWelcome.setText("Welcome, " + admin.getName() + "!");
        initializeTabels();
    }

    @FXML
    private void handleViewTravels() {
        loadModelTravels();
        mainTabPane.getSelectionModel().select(0);
    }

    @FXML
    private void handleAddTravel() {
        String destination = txtDestination.getText().trim();
        String transportCompany = txtTransportCompany.getText().trim();
        LocalDate departureDate = dtpDataDeparture.getValue();
        String departureTimeStr = txtTimeDeparture.getText().trim();
        String numberOfAvailableSeatsStr = txtNumberOfAvailableSeats.getText().trim();
        String priceStr = txtPrice.getText().trim();

        if (destination.isEmpty() || transportCompany.isEmpty() || departureDate == null ||
                departureTimeStr.isEmpty() || numberOfAvailableSeatsStr.isEmpty() || priceStr.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please complete all the fields!");
            return;
        }

        try {
            LocalTime departureTime = LocalTime.parse(departureTimeStr, DateTimeFormatter.ofPattern("HH:mm"));
            Integer numberOfAvailableSeats = Integer.parseInt(numberOfAvailableSeatsStr);
            Double price = Double.parseDouble(priceStr);

            LocalDateTime departureDateTime = LocalDateTime.of(departureDate, departureTime);

            service.addTravel(destination, departureDateTime,transportCompany, numberOfAvailableSeats, price);
            loadModelTravels();
            clearFields();
        } catch (NumberFormatException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Invalid number format!");
        } catch (ServiceException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Invalid date/time format!");
        }
    }

    @FXML
    private void handleAddAgent() {
        String name = txtName.getText().trim();
        String username = txtUsername.getText().trim();
        String password = txtPassword.getText().trim();

        if (name.isEmpty() || username.isEmpty() || password.isEmpty()) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please complete all the fields!");
            return;
        }

        try {
            service.addUser(name, username, password, loggedAdmin.getAgencyName(), Status.AGENT);
            clearFields();
        } catch (ServiceException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    private void clearFields() {
        txtDestination.clear();
        txtTimeDeparture.clear();
        txtTransportCompany.clear();
        txtNumberOfAvailableSeats.clear();
        txtPrice.clear();
        txtName.clear();
        txtUsername.clear();
        txtPassword.clear();
    }

    @FXML
    private void handleLogout() {
        stage.close();
    }
}