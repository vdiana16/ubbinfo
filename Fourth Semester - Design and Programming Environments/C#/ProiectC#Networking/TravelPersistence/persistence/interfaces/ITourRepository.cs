using TravelModel.model;

namespace TravelPersistence.persistence.interfaces;

public interface ITourRepository: IRepository<int, Tour>
{
    Tour? FindTour(string destination, string transportCompany, DateTime departureDate, double price,
        int numberOfAvailableSeats);
    
    Tour? UpdateSeats(int id, int seatsReserved);
    
    IEnumerable<Tour> FindToursByDestination(string destination);
}