using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using log4net;
using TravelModel.model;
using TravelServices.services;

namespace TravelNetworking.networking.jsonprotocol;

public class TravelClientJsonWorker : ITravelObserver
{
    private ITravelServices server;
    private TcpClient connection;
    
    private NetworkStream networkStream;
    private volatile bool connected;
    private static readonly ILog logger = LogManager.GetLogger(typeof(TravelClientJsonWorker));

    public TravelClientJsonWorker(ITravelServices server, TcpClient connection)
    {
        this.server = server;
        this.connection = connection;
        try
        {
            networkStream = connection.GetStream();
            connected = true;
        }
        catch (Exception ex)
        {
            logger.Error(ex.Message);
        }
    }

    public virtual void run()
    {
        using StreamReader streamReader = new StreamReader(connection.GetStream(), Encoding.UTF8);
        while (connected)
        {
            try
            {
                string requestJson = streamReader.ReadLine();
                if (string.IsNullOrEmpty(requestJson))
                {
                    logger.Error("Received empty request");
                    continue;
                }

                logger.DebugFormat("Received request: {0}", requestJson);
                Request request = JsonSerializer.Deserialize<Request>(requestJson);
                logger.DebugFormat("Received request: {0}", requestJson);
                Response response = handleRequest(request);
                if (response != null)
                {
                    sendResponse(response);
                }
            }
            catch (Exception ex)
            {
                logger.ErrorFormat("Error processing request: {0}", ex.Message);
                if (ex.InnerException != null)
                {
                    logger.ErrorFormat("Inner exception: {0}", ex.InnerException.Message);
                }

                logger.Error(ex.StackTrace);
            }

            try
            {
                Thread.Sleep(1000);
            }
            catch (Exception ex)
            {
                logger.Error("Error sleeping thread: " + ex.Message);
            }
        }
    }

    private static Response okResponse = JSonProtocolUtils.CreateOkResponse();

    private void sendResponse(Response response)
    {
        String jsonStr = JsonSerializer.Serialize(response);
        logger.DebugFormat("Sending response: {0}", jsonStr);
        lock (networkStream)
        {
            byte[] buffer = Encoding.UTF8.GetBytes(jsonStr + "\n");
            networkStream.Write(buffer, 0, buffer.Length);
            networkStream.Flush();
        }
    }

    public void tourModified(Tour tour)
    {
        Response response = JSonProtocolUtils.CreateTourModifiedResponse(tour);
        logger.Debug("Sending tour modified response");
        try
        {
            sendResponse(response);
        }
        catch (IOException ex)
        {
            logger.Error("Error sending tour modified response: " + ex.Message);
        }
    }
    
    private Response handleRequest(Request request)
    {
        Response response = null;
        if (request.RequestType == RequestType.LOGIN)
        {
            logger.DebugFormat("Received login request");
            try
            {
                Agent agent = null;
                lock (server)
                {
                    agent = server.login(request.Username, request.Password, this);
                }

                return JSonProtocolUtils.CreateLoginResponse(agent);
            }
            catch (ServiceException ex)
            {
                connected = false;
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
        }

        if (request.RequestType == RequestType.LOGOUT)
        {
            logger.DebugFormat("Received logout request");
            try
            {
                var agent = request.Agent;
                lock (server)
                {
                    server.logout(agent);
                }
            } 
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
            connected = false;
            return okResponse;
        }

        if (request.RequestType == RequestType.ADD_AGENT)
        {
            logger.DebugFormat("Received add agent request");
            var agent = request.Agent;
            try
            {
                server.AddAgent(agent);
                return okResponse;
            }
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
        }

        if (request.RequestType == RequestType.ADD_RESERVATION)
        {
            logger.DebugFormat("Received add agent request");
            var reservation = request.Reservation;
            try
            {
                server.AddReservation(reservation);
                return okResponse;
            }
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
        }

        if (request.RequestType == RequestType.GET_ALL_TOURS)
        {
            logger.DebugFormat("Received get all tours request");
            try
            {
                var tours = server.GetAllTours();
                return JSonProtocolUtils.CreateGetAllToursResponse(tours);
            }
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
        }
        
        if (request.RequestType == RequestType.GET_ALL_RESERVATIONS)
        {
            logger.DebugFormat("Received get all reservations request");
            try
            {
                var reservations = server.GetAllReservations();
                return JSonProtocolUtils.CreateGetAllReservationsResponse(reservations);
            }
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
        }

        if (request.RequestType == RequestType.GET_TOURS_BY_DESTINATION)
        {
            logger.DebugFormat("Received get all tours request");
            var destination = request.Destination;
            var departureDate = request.DepartureDate;
            var startTime = request.StartTime;
            var endTime = request.EndTime;
            try
            {
                var tours = server.GetToursByDestination(destination, departureDate, startTime, endTime);
                return JSonProtocolUtils.CreateGetToursByDestinationResponse(tours);
            }
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
        }

        if (request.RequestType == RequestType.GET_TOUR_BY_ID)
        {
            logger.DebugFormat("Received get tour by id request");
            var id = request.Id;
            try
            {
                var tour = server.GetTourById(id);
                return JSonProtocolUtils.CreateGetTourByIdResponse(tour);
            }
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
        }
        
        if (request.RequestType == RequestType.LOGOUT_FOR_SIGNUP)
        {
            logger.DebugFormat("Received logout for signup request");
            try
            {
                lock (server)
                {
                    server.logoutForSignUp();
                }
            } 
            catch (ServiceException ex)
            {
                return JSonProtocolUtils.CreateErrorResponse(ex.Message);
            }
            connected = false;
            return okResponse;
        }
        
        return response;
    }
}