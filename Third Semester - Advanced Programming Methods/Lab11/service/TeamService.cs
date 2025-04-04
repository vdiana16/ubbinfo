using lab11.domain;
using lab11.domain.validator;
using lab11.repository;
using lab11.utils;

namespace lab11.service;

public class TeamService
{
    private IRepository<int, Team> _teamRepository;
    private static readonly IValidator<Team> _teamValidator = new TeamValidator(); 
    
    public TeamService(){}

    public TeamService(IRepository<int, Team> teamRepository)
    {
        _teamRepository = teamRepository;
    }

    public Team? Add(Team team)
    {
        _teamValidator.Validate(team);
        team.Id = Util.GenerateId(GetAll());
        return _teamRepository.Add(team);
    }

    public Team? Update(Team team)
    {
        _teamValidator.Validate(team);
        return _teamRepository.Update(team);
    }

    public Team? Delete(int id)
    {
        return _teamRepository.Delete(id);
    }

    public Team? Get(int id)
    {
        return _teamRepository.Get(id);
    }

    public IEnumerable<Team> GetAll()
    {
        return _teamRepository.GetAll();
    }
}