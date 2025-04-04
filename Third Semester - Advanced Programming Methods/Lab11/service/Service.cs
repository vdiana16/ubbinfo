using System.Net;
using System.Reflection;
using lab11.domain;
using lab11.exception;

namespace lab11.service;

public delegate Student? GetStudent(int id);
public delegate Team? GetTeam(int id);

public class Service
{
    private readonly TeamService _teamService;
    private readonly StudentService _studentService;
    private readonly PlayerService _playerService;
    private readonly MatchService _matchService;
    private readonly ActivePlayerService _activePlayerService;

    public Service()
    {
    }

    public Service(TeamService teamService, StudentService studentService, PlayerService playerService,
        MatchService matchService, ActivePlayerService activePlayerService)
    {
        _teamService = teamService;
        _studentService = studentService;
        _playerService = playerService;
        _matchService = matchService;
        _activePlayerService = activePlayerService;
    }

    public Student? AddStudent(Student student)
    {
        return _studentService.Add(student);
    }

    public Team? AddTeam(Team team)
    {
        return _teamService.Add(team);
    }

    public Player? AddPlayer(Player player)
    {
        if (GetTeam(player.Team.Id) == default)
        {
            throw new ServiceException("Team doesn't exist");
        }

        AddStudent(player);
        return _playerService.Add(player);
    }

    public Match? AddMatch(Match match)
    {
        return _matchService.Add(match);
    }

    public ActivePlayer? AddActivePlayer(ActivePlayer activePlayer)
    {
        return _activePlayerService.Add(activePlayer);
    }

    public Player? DeletePlayer(int id)
    {
        return _playerService.Delete(id);
    }

    public Match? DeleteMatch(int id)
    {
        return _matchService.Delete(id);
    }

    public ActivePlayer? DeleteActivePlayer(int id)
    {
        return _activePlayerService.Delete(id);
    }

    public Team? DeleteTeam(int id)
    {
        var result = _teamService.Delete(id);
        if (result != default)
        {
            DeleteMatchWithTeam(result);
            DeletePlayerFromTeam(result);
        }

        return result;
    }

    public Student? DeleteStudent(int id)
    {
        var result = _studentService.Delete(id);
        DeletePlayer(id);
        return result;
    }

    public Student? UpdateStudent(Student student)
    {
        return _studentService.Update(student);
    }

    public Player? UpdatePlayer(Player player)
    {
        if (GetTeam(player.Team.Id) == default)
        {
            throw new ServiceException("Team doesn't exist");
        }

        UpdateStudent(player);
        return _playerService.Update(player);
    }

    public Match? UpdateMatch(Match match)
    {
        return _matchService.Update(match);
    }

    public ActivePlayer? UpdateActivePlayer(ActivePlayer activePlayer)
    {
        return _activePlayerService.Update(activePlayer);
    }

    public Team? GetTeam(int id)
    {
        return _teamService.Get(id);
    }

    public Student? GetStudent(int id)
    {
        return _studentService.Get(id);
    }

    public Player? GetPlayer(int id)
    {
        return _playerService.Get(id);
    }

    public Match? GetMatch(int id)
    {
        return _matchService.Get(id);
    }

    public ActivePlayer? GetActivePlayer(int id)
    {
        return _activePlayerService.Get(id);
    }

    public IEnumerable<Team> GetTeams()
    {
        return _teamService.GetAll();
    }

    public IEnumerable<Student> GetStudents()
    {
        return _studentService.GetAll();
    }

    public IEnumerable<Player> GetPlayers()
    {
        return _playerService.GetAll();
    }

    public IEnumerable<Match> GetMatches()
    {
        return _matchService.GetAll();
    }

    public IEnumerable<ActivePlayer> GetActivePlayers()
    {
        return _activePlayerService.GetAll();
    }

    private void DeleteMatchWithTeam(Team team)
    {
        GetMatches()
            .Where(m => m.FirstTeam == team || m.SecondTeam == team)
            .ToList()
            .ForEach(m => DeleteMatch(m.Id));
    }

    private void DeletePlayerFromTeam(Team team)
    {
        GetPlayers()
            .Where(p => p.Team == team)
            .ToList()
            .ForEach(p => DeletePlayer(p.Id));
    }

    public IEnumerable<Player>? GetAllPlayersOfATeam(Team team)
    {
        return _playerService.GetAllPlayerOfATeam(team);
    }

    public IEnumerable<IGrouping<Team, ActivePlayer>> GetAllActivePlayersOfATeamFromAMatch(Match match)
    {
        return GetActivePlayers().Where(activePlayer => activePlayer.IdMatch == match.Id)
            .ToList()
            .GroupBy(activePlayer => GetPlayer(activePlayer.IdPlayer).Team);
    }

    public IEnumerable<Match> GetAllMatchesFromAPeriod(DateTime st, DateTime end)
    {
        return _matchService.GetAllMatchesFromAPeriod(st, end);
    }

    public Dictionary<Team, int> GetScoreOfAMatch(Match match)
    {
        return GetAllActivePlayersOfATeamFromAMatch(match)
            .ToDictionary(g => g.Key, g => g.Sum(activePlayer => activePlayer.NumberOfPointsEntered));
    }
}