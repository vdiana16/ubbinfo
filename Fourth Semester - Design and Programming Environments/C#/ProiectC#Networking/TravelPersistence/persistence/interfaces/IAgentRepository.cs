using TravelModel.model;

namespace TravelPersistence.persistence.interfaces;

public interface IAgentRepository : IRepository<int, Agent>
{
    Agent? FindByUsername(string username, string password);
}