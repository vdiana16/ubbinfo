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
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.time.LocalDate;
import java.time.LocalTime;
import java.util.List;

public class TravelClientRpcReflectionWorker implements Runnable, TravelObserver {
    private TravelServices server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;
    private static Logger logger = LogManager.getLogger(TravelClientRpcReflectionWorker.class);
    public TravelClientRpcReflectionWorker(TravelServices server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try{
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            connected = true;
            logger.info("Client connected");
        } catch (IOException e) {
            logger.error("Error reading response: " + e.getMessage());
        }
    }

    @Override
    public void run(){
        while(connected){
            try {
                Object request=input.readObject();
                Response response=handleRequest((Request)request);
                if (response!=null){
                    sendResponse(response);
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            System.out.println("Error "+e);
        }
    }

    private static Response okResponse = new Response.Builder().type(ResponseType.OK).build();

    private Response handleRequest(Request request) {
        Response response = null;
        String handlerName = "handle" + (request).type();
        logger.debug("Handler name: " + handlerName);
        try {
            Method method = this.getClass().getDeclaredMethod(handlerName, Request.class);
            response = (Response) method.invoke(this, request);
            logger.debug("Method invoked " + handlerName);
        } catch (NoSuchMethodException | IllegalAccessException | InvocationTargetException e) {
            logger.error("Error reading response: " + e.getMessage());
            logger.error(e.getStackTrace());
        }
        return response;
    }

    private void sendResponse(Response response) throws IOException {
        logger.debug("Sending response: " + response);
        if (response != null) {
            output.writeObject(response);
            output.flush();
        }
    }

    private Response handleLOGIN(Request request){
        logger.info("Handling login request");
        Agent agent = (Agent) request.data();
        try{
            Agent loggedInAgent = server.login(agent.getUsername(), agent.getPassword(), this);
            logger.info("Login successful, sending OK response");
            return new Response.Builder().type(ResponseType.OK).data(loggedInAgent).build();
        } catch (ServiceException e){
            logger.info("Login failed, sending ERROR response: " + e.getMessage());
            connected = false;
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleADD_RESERVATION(Request request){
        Reservation reservation = (Reservation) request.data();
        try{
            server.addReservation(reservation);
            return new Response.Builder().type(ResponseType.OK).data(reservation).build();
        } catch (ServiceException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleGET_ALL_TOURS(Request request){
        logger.info("Getting tourss");
        try{
            return new Response.Builder().type(ResponseType.GET_ALL_TOURS).data(server.getAllTours()).build();
        } catch (ServiceException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleGET_ALL_RESERVATIONS(Request request){
        logger.info("Getting reservations");
        try{
            return new Response.Builder().type(ResponseType.GET_ALL_RESERVATIONS).data(server.getAllReservations()).build();
        } catch (ServiceException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleGET_TOURS_BY_DESTINATION(Request request){
        List<Object> data = (List<Object>) request.data();
        String destination = (String) data.get(0);
        LocalDate departureDate = (LocalDate) data.get(1);
        LocalTime startTime = (LocalTime) data.get(2);
        LocalTime endTime = (LocalTime) data.get(3);
        try{
            return new Response.Builder().type(ResponseType.GET_TOURS_BY_DESTINATION).data(server.getToursByDestination(destination, departureDate, startTime, endTime)).build();
        } catch (ServiceException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    public Response handleADD_AGENT(Request request){
        Agent agent = (Agent) request.data();
        try{
            server.addAgent(agent);
            return new Response.Builder().type(ResponseType.OK).data(agent).build();
        } catch (ServiceException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleLOGOUT(Request request){
        Agent agent = (Agent) request.data();
        try{
            server.logout(agent, this);
            connected = false;
            return okResponse;
        } catch (ServiceException e){
            logger.error("Error logging out: " + e.getMessage());
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleCLOSE(Request request){
        Agent agent = (Agent) request.data();
        try{
            server.logoutForSignUp(agent);
            connected = false;
            return okResponse;
        } catch (ServiceException e){
            logger.error("Error logging out: " + e.getMessage());
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    @Override
    public void tourModified(Tour tour) throws ServiceException{
        Response response = new Response.Builder().type(ResponseType.MODIFIED_TOUR).data(tour).build();
        try {
            sendResponse(response);
        } catch (IOException e) {
            logger.error("Error sending tour modified response: " + e.getMessage());
        }
    }
}
