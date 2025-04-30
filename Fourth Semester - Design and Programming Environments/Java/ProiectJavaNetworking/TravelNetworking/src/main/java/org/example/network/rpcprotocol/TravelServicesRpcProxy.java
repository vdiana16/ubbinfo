package org.example.network.rpcprotocol;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.model.Agent;
import org.example.model.Reservation;
import org.example.model.Tour;
import org.example.services.ServiceException;
import org.example.services.TravelObserver;
import org.example.services.TravelServices;


import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.time.LocalDate;
import java.time.LocalTime;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class TravelServicesRpcProxy implements TravelServices {
    private String host;
    private int port;

    private TravelObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private BlockingQueue<Response> qresponses;
    private volatile boolean finished;

    protected static Logger logger = LogManager.getLogger(String.valueOf(TravelServicesRpcProxy.class));

    public TravelServicesRpcProxy(){
        super();
    }

    public TravelServicesRpcProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses = new LinkedBlockingQueue<Response>();
    }

    private void closeConnection(){
        finished = true;
        try{
            input.close();
            output.close();
            connection.close();
            client = null;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendRequest(Request request) throws ServiceException {
        try {
            output.writeObject(request);
            output.flush();
            logger.info("Request sent successfully");
        } catch (IOException e) {
            logger.error("Failed to send request: " + e.getMessage());
            throw new ServiceException("Error sending request: " + e.getMessage());
        }
    }

    private Response readResponse() throws ServiceException {
        Response response = null;
        try {
            response = qresponses.take();
        } catch (InterruptedException e) {
            logger.error("Error reading response: " + e.getMessage());
            logger.error(e.getStackTrace());
        }
        return response;
    }

    private void initializeConnection() throws ServiceException {
        try {
            connection = new Socket(host, port);
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            finished = false;
            startReader();
            logger.info("Connection initialized successfully");
        } catch (IOException e) {
            logger.error("Error reading response in initializeConnection: " + e.getMessage());
            logger.error(e.getStackTrace());
        }
    }

    private boolean isUpdate(Response response) {
        return response.type() == ResponseType.MODIFIED_TOUR;
    }

    private void handleUpdate(Response response) {
        if (response.type() == ResponseType.MODIFIED_TOUR) {
            Tour tour = (Tour) response.data();
            logger.debug("Tour modified: " + tour);
            try{
                client.tourModified(tour);
            } catch (ServiceException e) {
                logger.error("Error reading response in handleUpdate: " + e.getMessage());
                logger.error(e.getStackTrace());
            }
        }
    }

    private class ReaderThread implements Runnable{
        public void run() {
            while (!finished) {
                try {
                    Object response = input.readObject();
                    logger.debug("Response received: " + response);
                    if (isUpdate((Response)response)) {
                        handleUpdate((Response)response);
                    } else {
                        try{
                            qresponses.put((Response) response);
                        } catch (InterruptedException e) {
                            logger.error("Error reading response im ReaderThread: " + e.getMessage());
                            logger.error(e.getStackTrace());
                            Thread.currentThread().interrupt();
                            break;
                        }
                    }
                } catch (IOException | ClassNotFoundException e) {
                    logger.error("Error reading response in ReaderThread: " + e.getMessage());
                    logger.error(e.getStackTrace());
                    closeConnection();
                }
            }
        }
    }

    private void startReader(){
        Thread thread = new Thread(new ReaderThread());
        thread.start();
    }

    @Override
    public Agent login(String username, String password, TravelObserver client) throws ServiceException {
        initializeConnection();
        Agent agent = new Agent("A",username, password);
        Request req = new Request.Builder().type(RequestType.LOGIN).data(agent).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.OK) {
            this.client = client;
            return (Agent) response.data();
        }
        if (response.type() == ResponseType.ERROR) {
            closeConnection();
            throw new ServiceException(response.data().toString());
        }
        return null;
    }

    @Override
    public void logout(Agent agent, TravelObserver client) throws ServiceException {
        Request req = new Request.Builder().type(RequestType.LOGOUT).data(agent).build();
        sendRequest(req);
        Response response = readResponse();
        closeConnection();
        if (response.type() == ResponseType.ERROR) {
            throw new ServiceException(response.data().toString());
        }
    }

    @Override
    public Tour[] getAllTours() throws ServiceException {
        Request req = new Request.Builder().type(RequestType.GET_ALL_TOURS).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new ServiceException(response.data().toString());
        }
        logger.info("Response received: " + response);
        return (Tour[]) response.data();
    }

    @Override
    public Reservation[] getAllReservations() throws ServiceException {
        Request req = new Request.Builder().type(RequestType.GET_ALL_RESERVATIONS).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new ServiceException(response.data().toString());
        }
        logger.info("Response received: " + response);
        return (Reservation[]) response.data();
    }

    @Override
    public List<Tour> getToursByDestination(String destination, LocalDate date, LocalTime startTime, LocalTime endTime) throws ServiceException {
        Request req = new Request.Builder().type(RequestType.GET_TOURS_BY_DESTINATION).data(Arrays.asList(destination, date, startTime, endTime)).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new ServiceException(response.data().toString());
        }
        logger.info("Response received: " + response);
        return (List<Tour>) response.data();
    }

    @Override
    public void addReservation(Reservation reservation) throws ServiceException {
        Request req = new Request.Builder().type(RequestType.ADD_RESERVATION).data(reservation).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new ServiceException(response.data().toString());
        }
        logger.info("Response received: " + response);
    }

    @Override
    public Agent addAgent(Agent agent) throws ServiceException{
        initializeConnection();
        Request req = new Request.Builder().type(RequestType.ADD_AGENT).data(agent).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new ServiceException(response.data().toString());
        }
        logger.info("Response received: " + response);
        return agent;
    }

    @Override
    public void logoutForSignUp(Agent agent) throws ServiceException {
        Request req = new Request.Builder().type(RequestType.CLOSE).data(agent).build();
        sendRequest(req);
        Response response = readResponse();
        closeConnection();
        if (response.type() == ResponseType.ERROR) {
            throw new ServiceException(response.data().toString());
        }
    }
}
