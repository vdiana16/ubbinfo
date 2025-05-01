using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using log4net;
using TravelServices.services;
using TravelModel.model;
using TravelServices.services;


namespace TravelNetworking.networking.jsonprotocol;

public class ServerJsonProxy : ITravelServices
{
    private String host;
    private int port;

    private ITravelObserver client;
    private NetworkStream stream;
    private TcpClient connection;
    private volatile bool finished = false;
    private EventWaitHandle waitHandle;
    private Queue<Response> responses;
    
    private static readonly ILog logger = LogManager.GetLogger(typeof(ServerJsonProxy));

    public ServerJsonProxy(String host, int port)
    {
        this.host = host;
        this.port = port;
        responses = new Queue<Response>();
    }

    private JSonProtocolUtils jsonProtocolUtils;

    public ITravelServices TravelServices { get; set; }

    private void initializeConnection()
    {
        try
        {
            connection = new TcpClient(host, port);
            stream = connection.GetStream();
            finished = false;
            waitHandle = new AutoResetEvent(false);
            startReader();
        }
        catch (Exception ex)
        {
            logger.Error(ex.StackTrace);
        }
    }

    private void startReader()
    {
        Thread thread = new Thread(run);
        thread.Start();
    }

    public virtual void run()
    {
        using StreamReader streamReader = new StreamReader(stream, Encoding.UTF8);
        while (!finished)
        {
            try
            {
                string responseJson = streamReader.ReadLine();
                Console.WriteLine("Raw JSON received: " + responseJson);
                if (string.IsNullOrEmpty(responseJson))
                {
                    Console.WriteLine("Received empty response");
                    continue;
                }

                Response response = JsonSerializer.Deserialize<Response>(responseJson);
                Console.WriteLine("Received response: " + response.ResponseType);
                logger.Debug("Response received: " + response);
                if (isUpdate(response))
                {
                    handleUpdate(response);
                }
                else
                {
                    lock (responses)
                    {
                        responses.Enqueue(response);
                    }

                    waitHandle.Set();
                }
            }
            catch (Exception ex)
            {
                logger.Error("Error reading response", ex);
            }
        }
    }

    private bool isUpdate(Response response)
    {
        return response.ResponseType == ResponseType.MODIFIED_TOUR;
    }

    private void handleUpdate(Response response)
    {
        logger.Debug("Received response: " + response.ResponseType);
        if (response.ResponseType == ResponseType.MODIFIED_TOUR)
        {
            var tour = response.Tour;
            try
            {
                client.tourModified(tour);
            }
            catch (Exception ex)
            {
                logger.Error("Error modifying tour", ex);
                logger.Error(ex.StackTrace);
            }
        }
    }
    
    private void sendRequest(Request request)
    {
        try
        {
            lock (stream)
            {
                string jsonReq = JsonSerializer.Serialize(request);
                logger.Debug("Sending request: " + jsonReq);
                byte[] buffer = Encoding.UTF8.GetBytes(jsonReq + "\n");
                stream.Write(buffer, 0, buffer.Length);
                stream.Flush();
            }
        }
        catch (Exception ex)
        {
            throw new ServiceException("Error sending request" + ex.Message);
        }
    }

    private Response readResponse()
    {
        Response response = null;
        try
        {
            waitHandle.WaitOne();
            lock (responses)
            {
                response = responses.Dequeue();
            }
        }
        catch (Exception ex)
        {
            logger.Error("Error reading response", ex);
        }
        return response;
    }

    private void closeConnection()
    {
        finished = true;
        try
        {
            stream.Close();
            connection.Close();
            waitHandle.Close();
            client = null;
        }
        catch (Exception ex)
        {
            logger.Error("Error closing connection", ex);
        }
    }
    
    public Agent AddAgent(Agent agent)
    {
        initializeConnection();
        logger.Info("Adding agent " + agent);
        Request request = JSonProtocolUtils.CreateAddAgentRequest(agent);
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            throw new ServiceException("Error while adding agent " + agent);
        }

        return response.Agent;
    }

    public Reservation AddReservation(Reservation reservation)
    {
        logger.Info("Adding reservation " + reservation);
        Request request = JSonProtocolUtils.CreateAddReservationRequest(reservation);
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            throw new ServiceException("Error while adding reservation " + reservation);
        }
        return response.Reservation;
    }
    
    public Agent login(String username, String password, ITravelObserver client)
    {
        initializeConnection();
        logger.Info("Logging in with username " + username);
        Agent agent = new Agent("A", username, password);
        Request request = JSonProtocolUtils.CreateLoginRequest(username, password);
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            closeConnection();
            throw new ServiceException("Error while logging in " + username);
        }

        this.client = client;
        return response.Agent;
    }

    public void logout(Agent agent)
    {
        Request request = JSonProtocolUtils.CreateLogoutRequest(agent);
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            closeConnection();
            throw new ServiceException("Error while logging out " + agent);
        }
        if (response.ResponseType == ResponseType.OK)
        {
            closeConnection();
        }
    }
    
    public IEnumerable<Tour> GetAllTours()
    {
        logger.Info("Getting all tours");
        Request request = JSonProtocolUtils.CreateGetAllToursRequest();
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            throw new ServiceException("Error while getting all tours");
        }
        return response.Tours;
    }

    public IEnumerable<Reservation> GetAllReservations()
    {
        logger.Info("Getting all reservations");
        Request request = JSonProtocolUtils.CreateGetAllReservationsRequest();
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            throw new ServiceException("Error while getting all reservations");
        }
        return response.Reservations;
    }

    public IEnumerable<Tour> GetToursByDestination(string destination, DateTime departureDate, TimeSpan startTime,
        TimeSpan endTime)
    {
        logger.Info("Getting tours by destination " + destination);
        Request request = JSonProtocolUtils.CreateGetTourByDestinationRequest(destination, departureDate, startTime,
            endTime);
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            throw new ServiceException("Error while getting tours by destination " + destination);
        }
        return response.ToursByDest;
    }

    public Tour GetTourById(int id)
    {
        logger.Info("Getting tour by id " + id);
        Request request = JSonProtocolUtils.CreateGetTourByIdRequest(id);
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            throw new ServiceException("Error while getting tour by id " + id);
        }
        return response.Tour;
    }

    public void logoutForSignUp()
    {
        Request request = JSonProtocolUtils.CreateLogoutForSignUpRequest();
        sendRequest(request);
        Response response = readResponse();
        if (response.ResponseType == ResponseType.ERROR)
        {
            closeConnection();
        }
        if (response.ResponseType == ResponseType.OK)
        {
            closeConnection();
        }
    }
}