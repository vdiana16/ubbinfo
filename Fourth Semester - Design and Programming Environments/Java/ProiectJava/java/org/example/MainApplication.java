package org.example;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.example.controller.LoginController;
import org.example.modul.Agent;
import org.example.modul.Reservation;
import org.example.modul.Trip;
import org.example.modul.validator.Validator;
import org.example.modul.validator.ValidatorFactory;
import org.example.modul.validator.ValidatorStrategy;
import org.example.repository.impl.AgentRepositoryImpl;
import org.example.repository.impl.ReservationRepositoryImpl;
import org.example.repository.impl.TripRepositoryImpl;
import org.example.repository.interfaces.AgentRepository;
import org.example.repository.interfaces.ReservationRepository;
import org.example.repository.interfaces.TripRepository;
import org.example.service.Service;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class MainApplication extends Application {
    private static Stage primaryStage;

    private Validator<Agent> agencyValidator;
    private Validator<Reservation> reservationValidator;
    private Validator<Trip> tripValidator;

    private AgentRepository agentRepository;
    private ReservationRepository reservationRepository;
    private TripRepository tripRepository;

    private Service service;


    @Override
    public void start(Stage primaryStage) throws Exception {
        Properties properties = new Properties();
        try{
            properties.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config " + e);
        }

        ValidatorFactory validatorFactory = ValidatorFactory.getInstance();
        this.agencyValidator = validatorFactory.createValidator(ValidatorStrategy.AGENCY);
        this.reservationValidator = validatorFactory.createValidator(ValidatorStrategy.RESERVATION);
        this.tripValidator = validatorFactory.createValidator(ValidatorStrategy.TRIP);

        this.agentRepository = new AgentRepositoryImpl(properties, agencyValidator);
        this.reservationRepository = new ReservationRepositoryImpl(properties, reservationValidator);
        this.tripRepository = new TripRepositoryImpl(properties, tripValidator);

        service = new Service(agentRepository, reservationRepository, tripRepository);

        initView(primaryStage);
        primaryStage.show();
    }

    private void initView(Stage primaryStage) {
        try {
            FXMLLoader stageLoader = new FXMLLoader();
            stageLoader.setLocation(getClass().getResource("/views/login-view.fxml"));
            AnchorPane setLayout = stageLoader.load();
            primaryStage.setTitle("Travel Agency");
            primaryStage.setScene(new Scene(setLayout, Color.POWDERBLUE));

            LoginController logInController = stageLoader.getController();
            logInController.setController(service, primaryStage);

        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Eroare la încărcarea login-view.fxml: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        launch(args);
    }

}