using TravelModel.model;

namespace TravelPersistence.persistence.interfaces;

public interface IReservationRepository: IRepository<int, Reservation>
{
    Reservation? FindReservation(int tourId, string nameClient, string contactClient, int numberOfReservedSeats);
    IEnumerable<Reservation> FindReservationsByTour(int tourId);
    IEnumerable<Reservation> FindReservationsByClient(string clientName);
}