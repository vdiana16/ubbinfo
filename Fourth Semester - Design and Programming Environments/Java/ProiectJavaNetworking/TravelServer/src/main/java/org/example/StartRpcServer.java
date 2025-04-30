package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.model.validator.ValidatorFactory;
import org.example.model.validator.ValidatorStrategy;
import org.example.network.utils.AbstractServer;
import org.example.network.utils.TravelRpcConcurrentServer;
import org.example.persistence.impl.AgentRepositoryImpl;
import org.example.persistence.impl.ReservationRepositoryImpl;
import org.example.persistence.impl.TourRepositoryImpl;
import org.example.persistence.interfaces.AgentRepository;
import org.example.persistence.interfaces.ReservationRepository;
import org.example.persistence.interfaces.TourRepository;
import org.example.server.TravelServicesImpl;
import org.example.services.ServiceException;
import org.example.services.TravelServices;

import java.io.IOException;
import java.util.Properties;

public class StartRpcServer {
    private static int defaultPort = 55555;
    private static Logger logger = LogManager.getLogger(StartRpcServer.class.getName());

    public static void main(String[] args){
        Properties serverProps = new Properties();
        try{
            serverProps.load(StartRpcServer.class.getResourceAsStream("/travelserver.properties"));
            logger.info("Properties loaded.");
            serverProps.list(System.out);
        } catch (IOException e){
            logger.error("Cannot find travelserver.properties " + e);
            return;
        }

        AgentRepository agentRepository = new AgentRepositoryImpl(serverProps, ValidatorFactory.getInstance().createValidator(ValidatorStrategy.AGENT));
        TourRepository tripRepository = new TourRepositoryImpl(serverProps, ValidatorFactory.getInstance().createValidator(ValidatorStrategy.TOUR));
        ReservationRepository reservationRepository = new ReservationRepositoryImpl(serverProps, ValidatorFactory.getInstance().createValidator(ValidatorStrategy.RESERVATION));

        TravelServices travelServices = new TravelServicesImpl(agentRepository, tripRepository, reservationRepository);

        int travelServerPort = defaultPort;
        try{
            travelServerPort = Integer.parseInt(serverProps.getProperty("travel.server.port"));
        } catch (NumberFormatException e){
            logger.error("Wrong port number " + e);
        }

        logger.info("Starting RPC server... {}", travelServerPort);
        AbstractServer server = new TravelRpcConcurrentServer(travelServerPort, travelServices);

        try {
            server.start();
        } catch (ServiceException e) {
            logger.error("Error starting server: " + e);
        } finally {
            try {
                server.stop();
            } catch (ServiceException e) {
                logger.error("Error stopping server: " + e);
            }
        }
    }
}
