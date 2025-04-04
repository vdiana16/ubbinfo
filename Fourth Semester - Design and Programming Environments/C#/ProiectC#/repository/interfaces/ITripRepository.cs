using TravelAgency.model;

namespace TravelAgency.repository;

public interface ITripRepository: IRepository<int, Trip>
{
    Trip? FindTrip(string destination, string transportCompany, DateTime departureDate, double price,
        int numberOfAvailableSeats);
    
    Trip? UpdateSeats(int id, int seatsReserved);
    
    IEnumerable<Trip> FindTripsByDestination(string destination);
}