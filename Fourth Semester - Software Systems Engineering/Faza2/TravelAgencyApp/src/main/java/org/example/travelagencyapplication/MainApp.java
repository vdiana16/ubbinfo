package org.example.travelagencyapplication;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.example.travelagencyapplication.controller.LoginController;
import org.example.travelagencyapplication.service.Service;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ConfigurableApplicationContext;

import java.io.IOException;

public class MainApp extends Application {
    private ConfigurableApplicationContext applicationContext;

    @Override
    public void init() {
        String[] args = getParameters().getRaw().toArray(new String[0]);

        this.applicationContext = new SpringApplicationBuilder()
                .sources(TravelAgencyMain.class)
                .run(args);
    }

    @Override
    public void stop(){
        this.applicationContext.close();
        Platform.exit();
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        FXMLLoader stageLoader = new FXMLLoader();
        stageLoader.setLocation(getClass().getResource("/views/login-view.fxml"));
        AnchorPane setLayout = stageLoader.load();
        primaryStage.setTitle("Travel Agency");
        primaryStage.setScene(new Scene(setLayout, Color.POWDERBLUE));


        LoginController logInController = stageLoader.getController();
        logInController.setController(applicationContext.getBean(Service.class), primaryStage);
        primaryStage.show();
    }

    public static void main(String[] args){
        launch();
    }
}
