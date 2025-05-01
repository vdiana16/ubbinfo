using TravelModel.model;

namespace TravelServices.services;

public interface ITravelObserver
{
    void tourModified(Tour tour);
}