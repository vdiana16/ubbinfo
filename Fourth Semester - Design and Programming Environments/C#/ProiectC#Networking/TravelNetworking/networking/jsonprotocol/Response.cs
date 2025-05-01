using TravelModel.model;

namespace TravelNetworking.networking.jsonprotocol;

public class Response
{
    public ResponseType ResponseType { get; set; }
    
    public Agent Agent { get; set; }
    
    public Reservation Reservation { get; set; }
    
    public Tour Tour { get; set; }
    
    public string ErroMessage { get; set; }

    public IEnumerable<Tour> Tours { get; set; }
    
    public IEnumerable<Tour> ToursByDest { get; set; }
    
    public IEnumerable<Reservation> Reservations { get; set; }
    
    
    public Response()
    {
        
    }
}