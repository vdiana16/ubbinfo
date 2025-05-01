using TravelModel.model;

namespace TravelNetworking.networking.jsonprotocol;

public class JSonProtocolUtils
{
    public static Request CreateLoginRequest(String username, String password)
    {
        return new Request { RequestType = RequestType.LOGIN, Username = username, Password = password };
    }

    public static Request CreateLogoutRequest(Agent agent)
    {
        return new Request { RequestType = RequestType.LOGOUT, Agent = agent };
    }
    
    public static Request CreateLogoutForSignUpRequest()
    {
        return new Request { RequestType = RequestType.LOGOUT_FOR_SIGNUP };
    }

    public static Request CreateAddAgentRequest(Agent agent)
    {
        return new Request { RequestType = RequestType.ADD_AGENT, Agent = agent };
    }

    public static Request CreateAddReservationRequest(Reservation reservation)
    {
        return new Request { RequestType = RequestType.ADD_RESERVATION, Reservation = reservation };
    }
    
    public static Request CreateGetAllToursRequest()
    {
        return new Request { RequestType = RequestType.GET_ALL_TOURS };
    }

    public static Request CreateGetAllReservationsRequest()
    {
        return new Request { RequestType = RequestType.GET_ALL_RESERVATIONS};
    }

    public static Request CreateGetTourByDestinationRequest(String destination, DateTime departureDate, TimeSpan startTime, TimeSpan endTime)
    {
        return new Request
        {
            RequestType = RequestType.GET_TOURS_BY_DESTINATION,
            Destination = destination,
            DepartureDate = departureDate,
            StartTime = startTime,
            EndTime = endTime
        };
    }
    
    public static Request CreateGetTourByIdRequest(int id)
    {
        return new Request { RequestType = RequestType.GET_TOUR_BY_ID, Id = id };
    }

    public static Response CreateOkResponse()
    {
        return new Response { ResponseType = ResponseType.OK };
    }

    public static Response CreateErrorResponse(String error)
    {
        return new Response { ResponseType = ResponseType.ERROR, ErroMessage = error };
    }
    
    public static Response CreateLoginResponse(Agent agent)
    {
        return new Response { ResponseType = ResponseType.LOGIN, Agent = agent };
    }

    public static Response CreateLogoutResponse(Agent agent)
    {
        return new Response { ResponseType = ResponseType.LOGOUT, Agent = agent };
    }
    
    public static Response CreateLogoutForSignUpResponse()
    {
        return new Response { ResponseType = ResponseType.LOGOUT_FOR_SIGNUP };
    }
    
    public static Response CreateAddAgentResponse(Agent agent)
    {
        return new Response { ResponseType = ResponseType.ADD_AGENT, Agent = agent };
    }
    
    public static Response CreateAddReservationResponse(Reservation reservation)
    {
        return new Response { ResponseType = ResponseType.ADD_RESERVATION, Reservation = reservation };
    }

    public static Response CreateGetAllToursResponse(IEnumerable<Tour> trips)
    {
        return new Response{ ResponseType = ResponseType.GET_ALL_TOURS, Tours = trips };
    }
    
    public static Response CreateGetAllReservationsResponse(IEnumerable<Reservation> reservations)
    {
        return new Response{ ResponseType = ResponseType.GET_ALL_RESERVATIONS, Reservations = reservations };
    }

    public static Response CreateGetToursByDestinationResponse(IEnumerable<Tour> trips)
    {
        return new Response{ ResponseType = ResponseType.GET_TOURS_BY_DESTINATION, ToursByDest = trips };
    }

    public static Response CreateTourModifiedResponse(Tour tour)
    {
        return new Response(){ResponseType = ResponseType.MODIFIED_TOUR, Tour = tour};
    }
    
    public static Response CreateGetTourByIdResponse(Tour tour)
    {
        return new Response(){ResponseType = ResponseType.GET_TOUR_BY_ID, Tour = tour};
    }
}