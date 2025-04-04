using TravelAgency.model;

namespace TravelAgency.repository;

public interface IAgentRepository : IRepository<int, Agent>
{
    Agent? FindByUsername(string username, string password);
}