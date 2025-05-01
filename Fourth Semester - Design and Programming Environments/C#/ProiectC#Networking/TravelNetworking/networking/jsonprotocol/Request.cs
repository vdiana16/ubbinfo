using TravelModel.model;

namespace TravelNetworking.networking.jsonprotocol;

public class Request
{
    public RequestType RequestType { get; set; }
    
    public Agent Agent { get; set; }
    
    public Tour Tour { get; set; }
    
    public int Id { get; set; }
    
    public Reservation Reservation { get; set; }
    
    public string Username { get; set; }
    
    public string Password { get; set; }
    
    public string Destination { get; set; }
    
    public DateTime DepartureDate { get; set; }
    
    public TimeSpan StartTime { get; set; }
    
    public TimeSpan EndTime { get; set; }
}