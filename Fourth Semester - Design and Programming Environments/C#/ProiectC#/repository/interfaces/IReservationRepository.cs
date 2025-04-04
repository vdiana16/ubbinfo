using TravelAgency.model;

namespace TravelAgency.repository;

public interface IReservationRepository: IRepository<int, Reservation>
{
    Reservation? FindReservation(int tripId, string nameClient, string contactClient, int numberOfReservedSeats);
    IEnumerable<Reservation> FindReservationsByTrip(int tripId);
    IEnumerable<Reservation> FindReservationsByClient(string clientName);
}