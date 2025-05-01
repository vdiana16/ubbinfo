using TravelModel.model;

namespace TravelServices.services;

public interface ITravelServices
{
    Agent login(String username, String password, ITravelObserver client);
    
    Agent AddAgent(Agent agent);
    
    IEnumerable<Tour> GetAllTours();
    IEnumerable<Tour> GetToursByDestination(string destination, DateTime departureDate, TimeSpan startTime, TimeSpan endTime);

    Reservation AddReservation(Reservation reservation);
    IEnumerable<Reservation> GetAllReservations();

    Tour GetTourById(int id);
    
    void logout(Agent agent);
    
    void logoutForSignUp();
}