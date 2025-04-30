package org.example.client.controller;

import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.example.model.Agent;
import org.example.model.Reservation;
import org.example.model.Tour;
import org.example.services.ServiceException;
import org.example.services.TravelObserver;
import org.example.services.TravelServices;


import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class MainController implements TravelObserver {
   private TravelServices server;
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
   private TableView<Tour> tableViewTours;
   @FXML
   private TableColumn<Tour, String> tblColumnDestination;
   @FXML
   private TableColumn<Tour, String> tblColumnTransportCompany;
   @FXML
   private TableColumn<Tour, String> tblColumnDepartureDate;
   @FXML
   private TableColumn<Tour, Double> tblColumnPrice;
   @FXML
   private TableColumn<Tour, Integer> tblColumnNumberOfAvailableSeats;

   @FXML
   private TableView<Tour> tableViewToursByDestination;
   @FXML
   private TableColumn<Tour, String> tblColumnDest;
   @FXML
   private TableColumn<Tour, String> tblColumnTranspComp;
   @FXML
   private TableColumn<Tour, String> tblColumnDepDate;
   @FXML
   private TableColumn<Tour, Double> tblColumnPr;
   @FXML
   private TableColumn<Tour, Integer> tblColumnNumOfAvSeats;

   @FXML
   private TableView<Reservation> tableViewReservations;
   @FXML
   private TableColumn<Reservation, String> tblColumnTourDestination;
   @FXML
   private TableColumn<Reservation, String> tblColumnClientName;
   @FXML
   private TableColumn<Reservation, String> tblColumnClientContact;
   @FXML
   private TableColumn<Reservation, Integer> tblColumnSeats;

   private ObservableList<Tour> modelTours;
   private ObservableList<Tour> modelToursByDestination;
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

       tblColumnTourDestination.setCellValueFactory(cellData -> {
           Tour tour = cellData.getValue().getTour();
           return new SimpleStringProperty(tour != null ? tour.getDestination() : "");
       });
       tblColumnClientName.setCellValueFactory(new PropertyValueFactory<>("clientName"));
       tblColumnClientContact.setCellValueFactory(new PropertyValueFactory<>("clientContact"));
       tblColumnSeats.setCellValueFactory(new PropertyValueFactory<>("numberOfReservedSeats"));

       tblColumnNumberOfAvailableSeats.setCellFactory(col -> new TableCell<Tour, Integer>(){
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

       modelTours = FXCollections.observableArrayList();
       modelToursByDestination = FXCollections.observableArrayList();
       modelReservations = FXCollections.observableArrayList();
       tableViewTours.setItems(modelTours);
       tableViewToursByDestination.setItems(modelToursByDestination);
       tableViewReservations.setItems(modelReservations);

       tableViewTours.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
   }


   private void loadModelTours() {
       modelTours.setAll(server.getAllTours());
   }

   private void loadModelReservations() {
       modelReservations.setAll(server.getAllReservations());
   }

   public void setController(TravelServices service, Stage stage, Agent agent) {
       this.server = service;
       this.stage = stage;
       this.loggedAgent = agent;

       lblWelcome.setText("Welcome, " + agent.getName() + "!");
       initializeTabels();
       loadModelTours();
       loadModelReservations();

       mainTabPane.getSelectionModel().selectedItemProperty().addListener((obs, oldTab, newTab) -> {
           if (newTab != null && newTab.getText().equals("Show Reservations")) {
               loadModelReservations();
           }
       });
   }

   @FXML
   private void handleSearchTours() {
       String destination = txtSearchedDestination.getText().trim();
       String dataDeparture = dtpDataDeparture.getValue().toString();
       String startTime = txtStartTime.getText().trim();
       String endTime = txtEndTime.getText().trim();

       try{
           LocalTime stTime = LocalTime.parse(startTime);
           LocalTime enTime = LocalTime.parse(endTime);
           LocalDate depDate = LocalDate.parse(dataDeparture);

           List<Tour> result = server.getToursByDestination(destination, depDate, stTime, enTime);

           modelToursByDestination.setAll(result);
           if (result.isEmpty()){
               MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Information", "No tours found!");
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
       Tour selectedTour = tableViewTours.getSelectionModel().getSelectedItem();
       if (selectedTour == null){
           MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "No tour selected!");
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
           if(seats > selectedTour.getNumberOfAvailableSeats()){
               MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Not enough available seats!");
               return;
           }
           Reservation reservation = new Reservation(selectedTour, clientName, clientContact, seats);
           server.addReservation(reservation);
           MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Information", "Reservation made successfully!");
           clearFields();
           loadModelTours();
       } catch (RuntimeException e) {
           MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
       }
   }

   @FXML
   private void handleLogout() {
       logout();
       stage.close();
   }

   public void logout(){
       try{
           server.logout(loggedAgent, this);
           System.out.println("Logout successful");
       } catch (ServiceException e) {
           MessageAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
       }
   }

   @Override
   public void tourModified(Tour tour) throws ServiceException {
       Platform.runLater(() -> {
           MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Information", "New reservation added!");
           loadModelTours();
           loadModelReservations();
       });
   }

}
