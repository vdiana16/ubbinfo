package org.example.controller;

import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.example.modul.Agent;
import org.example.modul.Reservation;
import org.example.modul.Trip;
import org.example.service.Service;
import org.example.utils.event.ChangeEventType;
import org.example.utils.event.TravelAgencyEventType;
import org.example.utils.observer.Observable;
import org.example.utils.observer.Observer;

import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class MainController implements Observer<TravelAgencyEventType> {
    private Service service;
    private Stage stage;
    private Agent loggedAgent;
    private static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm dd/MM/yyyy");


    @FXML
    private TabPane mainTabPane;

    @FXML
    private Label lblWelcome;

    @FXML
    private TextField txtSearchedDestination;

    @FXML
    private TextField txtStartTime;

    @FXML
    private TextField txtEndTime;

    @FXML
    private DatePicker dtpDataDeparture;

    @FXML
    private TextField txtClientName;

    @FXML
    private TextField txtClientContact;

    @FXML
    private TextField txtReservedSeats;

    @FXML
    private TableView<Trip> tableViewTrips;
    @FXML
    private TableColumn<Trip, String> tblColumnDestination;
    @FXML
    private TableColumn<Trip, String> tblColumnTransportCompany;
    @FXML
    private TableColumn<Trip, String> tblColumnDepartureDate;
    @FXML
    private TableColumn<Trip, Double> tblColumnPrice;
    @FXML
    private TableColumn<Trip, Integer> tblColumnNumberOfAvailableSeats;

    @FXML
    private TableView<Trip> tableViewTripsByDestination;
    @FXML
    private TableColumn<Trip, String> tblColumnDest;
    @FXML
    private TableColumn<Trip, String> tblColumnTranspComp;
    @FXML
    private TableColumn<Trip, String> tblColumnDepDate;
    @FXML
    private TableColumn<Trip, Double> tblColumnPr;
    @FXML
    private TableColumn<Trip, Integer> tblColumnNumOfAvSeats;

    @FXML
    private TableView<Reservation> tableViewReservations;
    @FXML
    private TableColumn<Reservation, String> tblColumnTripDestination;
    @FXML
    private TableColumn<Reservation, String> tblColumnClientName;
    @FXML
    private TableColumn<Reservation, String> tblColumnClientContact;
    @FXML
    private TableColumn<Reservation, Integer> tblColumnSeats;

    private ObservableList<Trip> modelTrips;
    private ObservableList<Trip> modelTripsByDestination;
    private ObservableList<Reservation> modelReservations;

    private void initializeTabels() {
        tblColumnDestination.setCellValueFactory(new PropertyValueFactory<>("destination"));
        tblColumnTransportCompany.setCellValueFactory(new PropertyValueFactory<>("transportCompany"));
        //tblColumnDepartureDate.setCellValueFactory(new PropertyValueFactory<>("departureDate"));
        tblColumnDepartureDate.setCellValueFactory(cellData -> {
            return new SimpleStringProperty(cellData.getValue().getDepartureDate().format(DATE_TIME_FORMATTER));
        });
        tblColumnPrice.setCellValueFactory(new PropertyValueFactory<>("price"));
        tblColumnNumberOfAvailableSeats.setCellValueFactory(new PropertyValueFactory<>("numberOfAvailableSeats"));

        tblColumnDest.setCellValueFactory(new PropertyValueFactory<>("destination"));
        tblColumnTranspComp.setCellValueFactory(new PropertyValueFactory<>("transportCompany"));
        tblColumnDepDate.setCellValueFactory(cellData -> {
            return new SimpleStringProperty(cellData.getValue().getDepartureDate().format(DATE_TIME_FORMATTER));
        });
        tblColumnPr.setCellValueFactory(new PropertyValueFactory<>("price"));
        tblColumnNumOfAvSeats.setCellValueFactory(new PropertyValueFactory<>("numberOfAvailableSeats"));

        tblColumnTripDestination.setCellValueFactory(cellData -> {
            Trip trip = cellData.getValue().getTrip();
            return new SimpleStringProperty(trip != null ? trip.getDestination() : "");
        });
        tblColumnClientName.setCellValueFactory(new PropertyValueFactory<>("clientName"));
        tblColumnClientContact.setCellValueFactory(new PropertyValueFactory<>("clientContact"));
        tblColumnSeats.setCellValueFactory(new PropertyValueFactory<>("numberOfReservedSeats"));

        tblColumnNumberOfAvailableSeats.setCellFactory(col -> new TableCell<Trip, Integer>(){
           @Override
           protected void updateItem(Integer item, boolean empty){
               super.updateItem(item, empty);
               if (empty){
                   setText(null);
                   setStyle("");
               } else {
                   setText(item.toString());
                   if (item <= 0){
                       setTextFill(Color.RED);
                   } else {
                       setTextFill(Color.BLACK);
                   }
               }
           }
        });

        modelTrips = FXCollections.observableArrayList();
        modelTripsByDestination = FXCollections.observableArrayList();
        modelReservations = FXCollections.observableArrayList();
        tableViewTrips.setItems(modelTrips);
        tableViewTripsByDestination.setItems(modelTripsByDestination);
        tableViewReservations.setItems(modelReservations);

        tableViewTrips.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }


    private void loadModelTrips() {
        modelTrips.setAll(service.findAllTrips());
    }

    private void loadModelReservations() {
        modelReservations.setAll(service.findAllReservations());
    }

    public void setController(Service service, Stage stage, Agent agent) {
        this.service = service;
        this.stage = stage;
        this.loggedAgent = agent;
        service.addObserver(this);

        lblWelcome.setText("Welcome, " + agent.getName() + "!");
        initializeTabels();
        loadModelTrips();
        loadModelReservations();

        mainTabPane.getSelectionModel().selectedItemProperty().addListener((obs, oldTab, newTab) -> {
            if (newTab != null && newTab.getText().equals("Show Reservations")) {
                loadModelReservations();
            }
        });
    }

    @FXML
    private void handleSearchTrips() {
        String destination = txtSearchedDestination.getText().trim();
        String dataDeparture = dtpDataDeparture.getValue().toString();
        String startTime = txtStartTime.getText().trim();
        String endTime = txtEndTime.getText().trim();

        try{
            LocalTime stTime = LocalTime.parse(startTime);
            LocalTime enTime = LocalTime.parse(endTime);
            LocalDate depDate = LocalDate.parse(dataDeparture);

            List<Trip> result = service.searchTripsByDestTime(destination, depDate, stTime, enTime);

            modelTripsByDestination.setAll(result);
            if (result.isEmpty()){
                MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Information", "No trips found!");
            }

        } catch (RuntimeException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    private void clearFields() {
        txtClientName.clear();
        txtClientContact.clear();
        txtReservedSeats.clear();
    }

    @FXML
    private void handleReservation(ActionEvent event){
        Trip selectedTrip = tableViewTrips.getSelectionModel().getSelectedItem();
        if (selectedTrip == null){
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "No trip selected!");
            return;
        }

        String clientName = txtClientName.getText().trim();
        String clientContact = txtClientContact.getText().trim();
        String reservedSeats = txtReservedSeats.getText().trim();

        if (clientName.isEmpty() || clientContact.isEmpty() || reservedSeats.isEmpty()){
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please complete all the fields!");
            return;
        }

        try{
            int seats = Integer.parseInt(reservedSeats);
            if (seats <= 0){
                MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Number of seats must be greater than 0!");
                return;
            }
            if(seats > selectedTrip.getNumberOfAvailableSeats()){
                MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Not enough available seats!");
                return;
            }
            Reservation reservation = new Reservation(selectedTrip, clientName, clientContact, seats);
            service.addReservation(reservation);
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Information", "Reservation made successfully!");
            clearFields();
            loadModelTrips();
        } catch (RuntimeException e) {
            MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    @FXML
    private void handleLogout() {
        stage.close();
    }

    @Override
    public void update(TravelAgencyEventType travelAgencyEventType) {
        if (travelAgencyEventType.getType() == ChangeEventType.RESERVEDSEAT) {
            initializeTabels();
            loadModelTrips();
        }
    }
}
