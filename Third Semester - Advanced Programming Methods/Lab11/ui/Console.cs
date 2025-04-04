using lab11.domain;
using lab11.exception;
using lab11.service;
using Type = lab11.domain.Type;

namespace lab11.ui;

public enum Domain
{
    Team, Student, Match, Player, ActivePlayer
}

public class Console
{
    private Service _service;
    
    public Console(Service service)
    {
        _service = service;
    }

    private static Team ReadTeam()
    {
        System.Console.WriteLine("Enter team name: ");
        var name = System.Console.ReadLine();
        return new Team(name);
    }

    private Student ReadStudent()
    {
        System.Console.WriteLine("Enter student name: ");
        var name = System.Console.ReadLine();
        System.Console.WriteLine("Enter school name: ");
        var school = System.Console.ReadLine();
        return new Student(name, school);
    }

    private Player? ReadPlayer()
    {
        System.Console.WriteLine("Enter student name: ");
        var stName = System.Console.ReadLine();
        System.Console.WriteLine("Enter school name: ");
        var schName = System.Console.ReadLine();
        try
        {
            System.Console.WriteLine("Enter team id: ");
            var teamId = int.Parse(System.Console.ReadLine());

            var team = _service.GetTeam(teamId);
            if (team != default)
            {
                return new Player(stName, schName, team);
            }
        }
        catch (System.FormatException)
        {
            System.Console.WriteLine("Invalid team id");
        }
        return default;
    }

    private Match? ReadMatch()
    {
        try
        {
            System.Console.WriteLine("Enter first team id: ");
            var firstTeamId = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter second team id: ");
            var secondTeamId = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter match day: ");
            var day = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter match month: ");
            var month = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter match year: ");
            var year = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter match hour: ");
            var hour = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter match minute: ");
            var minute = int.Parse(System.Console.ReadLine());
            var firstTeam = _service.GetTeam(firstTeamId);
            var secondTeam = _service.GetTeam(secondTeamId);
            
            try
            {
                var dateMatch = new DateTime(year, month, day, hour, minute, 0);

                if (firstTeam != default && secondTeam != default)
                {
                    return new Match(firstTeam, secondTeam, dateMatch);
                }
            }
            catch (System.FormatException er)
            {
                System.Console.WriteLine(er.Message);
            }
        }
        catch (System.FormatException er)
        {
            System.Console.WriteLine(er.Message);
        }
        return default;
    }

    private ActivePlayer? ReadActivePlayer()
    {
        try
        {
            System.Console.WriteLine("Enter player id: ");
            var playerId = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter match id: ");
            var matchId = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter number of points entered: ");
            var points = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Enter type --Scrub/Participant--: ");
            var type = System.Console.ReadLine();
            
            if(type is "Scrub" or "Participant")
                return new ActivePlayer(playerId, matchId, points, (Type)Enum.Parse(typeof(Type), type));
            
            System.Console.WriteLine("Invalid type");
        }
        catch (System.FormatException er)
        {
            System.Console.WriteLine(er.Message);
        }
        return default;
    }

    private void Add(Domain domain)
    {
        try
        {
            switch (domain)
            {
                case Domain.Team:
                    _service.AddTeam(ReadTeam());
                    break;
                case Domain.Student:
                    _service.AddStudent(ReadStudent());
                    break;
                case Domain.Match:
                    _service.AddMatch(ReadMatch());
                    break;
                case Domain.Player:
                    _service.AddPlayer(ReadPlayer());
                    break;
                case Domain.ActivePlayer:
                    _service.AddActivePlayer(ReadActivePlayer());
                    break;
                default:
                    System.Console.WriteLine("Invalid domain");
                    break;
            }
        }
        catch (ValidationException e)
        {
            System.Console.WriteLine(e.Message);
        }
        catch (ServiceException e)
        {
            System.Console.WriteLine(e.Message);
        }
        catch (ArgumentNullException e)
        {
            System.Console.WriteLine(e.Message);
        }
    }

    private void Delete(Domain domain)
    {
        try
        {
            System.Console.WriteLine("Enter id: ");
            var id = int.Parse(System.Console.ReadLine());
            switch (domain)
            {
                case Domain.Team:
                    _service.DeleteTeam(id);
                    break;
                case Domain.Student:
                    _service.DeleteStudent(id);
                    break;
                case Domain.Match:
                    _service.DeleteMatch(id);
                    break;
                case Domain.Player:
                    _service.DeletePlayer(id);
                    break;
                case Domain.ActivePlayer:
                    _service.DeleteActivePlayer(id);
                    break;
                default:
                    System.Console.WriteLine("Invalid domain");
                    break;
            }
        }
        catch (ValidationException e)
        {
            System.Console.WriteLine(e.Message);
        }
        catch (ServiceException e)
        {
            System.Console.WriteLine(e.Message);
        }
        catch (ArgumentNullException e)
        {
            System.Console.WriteLine(e.Message);
        }
    }

    private void ShowAll(Domain domain)
    {
        IEnumerable<Entity<int>> entities = default;

        switch (domain)
        {
            case Domain.Team:
                entities = _service.GetTeams();
                break;
            case Domain.Student:
                entities = _service.GetStudents();
                break;
            case Domain.Match:
                entities = _service.GetMatches();
                break;
            case Domain.Player:
                entities = _service.GetPlayers();
                break;
            case Domain.ActivePlayer:
                entities = _service.GetActivePlayers();
                break;
            default:
                System.Console.WriteLine("Invalid domain");
                break;
        }

        if (!entities.Any())
        {
            System.Console.WriteLine("No entities found");
        }
        else
        {
            entities
                .ToList()
                .ForEach(e => System.Console.WriteLine(e));
        }
    }

    private void ShowAllPlayersOfATeam()
    {
        try
        {
            System.Console.WriteLine("Team id: ");
            var id = int.Parse(System.Console.ReadLine());

            var team = _service.GetTeam(id);
            
            var players = _service.GetAllPlayersOfATeam(team);
            
            if (players != default && players.Any())
                players
                        .ToList()
                        .ForEach(System.Console.WriteLine);
            else
            {
                System.Console.WriteLine("No entities found!");
            }
        }
        catch (IOException e)
        {
            System.Console.WriteLine(e.Message);
        }
    }
    
    private void ShowAllActivePlayersOfATeamFromAMatch()
    {
        System.Console.WriteLine("Match id: ");
        var id = int.Parse(System.Console.ReadLine());
        
        var match = _service.GetMatch(id);

        if (match == default)
        {
            System.Console.WriteLine("No entities found!");
            return;
        }
        
        var activePlayers = _service.GetAllActivePlayersOfATeamFromAMatch(match);
        foreach (var team in activePlayers)
        {
            System.Console.WriteLine("Team: " + team.Key + ": ");
            foreach (var activePlayer in team)
            { 
                System.Console.WriteLine($"Id: {activePlayer.Id} Name: {_service.GetPlayer(activePlayer.IdPlayer)?.Name} " +
                                         $"Numbers of points: {activePlayer.NumberOfPointsEntered} Type: {activePlayer.Type}");
            }
        }
        
        System.Console.ResetColor();
    }
    
    public void ShowAllMatchesFromATimePeriod()
    {
        try
        {
            System.Console.WriteLine("Start time:\nDay: ");
            var sday = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Month: ");
            var smonth = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Year: ");
            var syear = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Hour: ");
            var shour = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Minute: ");
            var sminute = int.Parse(System.Console.ReadLine());

            System.Console.WriteLine("End time:\nDay: ");
            var eday = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Month: ");
            var emonth = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Year: ");
            var eyear = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Hour: ");
            var ehour = int.Parse(System.Console.ReadLine());
            System.Console.WriteLine("Minute: ");
            var eminute = int.Parse(System.Console.ReadLine());

            try
            {
                var stTime = new DateTime(syear, smonth, sday, shour, sminute, 0);
                var endTime = new DateTime(eyear, emonth, eday, ehour, eminute, 0);
                _service.GetAllMatchesFromAPeriod(stTime, endTime)
                    .ToList()
                    .ForEach(System.Console.WriteLine);
            }
            catch (ArgumentOutOfRangeException e)
            {
                System.Console.WriteLine(e.Message);
            }
        }
        catch (IOException e)
        {
            System.Console.WriteLine(e.Message);
        }
    }
    
    private void ShowScoreOfAMatch()
    {
        System.Console.WriteLine("Match id: ");
        try
        {
            var id = int.Parse(System.Console.ReadLine());

            var match = _service.GetMatch(id);

            if (match == null)
            {
                System.Console.WriteLine("There are no results!");
                return;
            }
            var score = _service.GetScoreOfAMatch(match);

            foreach (var scoreOfTeam in score)
            {
                System.Console.WriteLine("Team- " + scoreOfTeam.Key.Name + " with score: " + scoreOfTeam.Value);
            }
        }
        catch (IOException e)
        {
            System.Console.WriteLine(e.Message);
        }
    }
    private void menu()
    {
        System.Console.WriteLine("Choose option:");
        System.Console.WriteLine("0. Exit");
        System.Console.WriteLine("1. Add team");
        System.Console.WriteLine("2. Delete team");
        System.Console.WriteLine("3. Show teams");
        System.Console.WriteLine("4. Add student");
        System.Console.WriteLine("5. Delete student");
        System.Console.WriteLine("6. Show students");
        System.Console.WriteLine("7. Add player");
        System.Console.WriteLine("8. Delete player");
        System.Console.WriteLine("9. Show players");
        System.Console.WriteLine("10. Add match");
        System.Console.WriteLine("11. Delete match");
        System.Console.WriteLine("12. Show matches");
        System.Console.WriteLine("13. Add active player");
        System.Console.WriteLine("14. Delete active player");
        System.Console.WriteLine("15. Show active players");
        System.Console.WriteLine("16. Show all team's players");
        System.Console.WriteLine("17. Show all team's active players from a match");
        System.Console.WriteLine("18. Show all matches from a time period");
        System.Console.WriteLine("19. Show score of a match");
    }

    public void Start()
    {
        bool finish = false;
        string input;
        while (!finish)
        {
            menu();
            System.Console.WriteLine("Choose option:");
            input = System.Console.ReadLine();
            switch (input)
            {
                case "0":
                    finish = true;
                    break;
                case "1":
                    Add(Domain.Team);
                    break;
                case "2":
                    Delete(Domain.Team);
                    break;
                case "3":
                    ShowAll(Domain.Team);
                    break;
                case "4":
                    Add(Domain.Student);
                    break;
                case "5":
                    Delete(Domain.Student);
                    break;
                case "6":
                    ShowAll(Domain.Student);
                    break;
                case "7":
                    Add(Domain.Player);
                    break;
                case "8":
                    Delete(Domain.Player);
                    break;
                case "9":
                    ShowAll(Domain.Player);
                    break;
                case "10":
                    Add(Domain.Match);
                    break;
                case "11":
                    Delete(Domain.Match);
                    break;
                case "12":
                    ShowAll(Domain.Match);
                    break;
                case "13":
                    Add(Domain.ActivePlayer);
                    break;
                case "14":
                    Delete(Domain.ActivePlayer);
                    break;
                case "15":
                    ShowAll(Domain.ActivePlayer);
                    break;
                case "16":
                    ShowAllPlayersOfATeam();
                    break;
                case "17": 
                    ShowAllActivePlayersOfATeamFromAMatch();
                    break;
                case "18":
                    ShowAllMatchesFromATimePeriod();
                    break;
                case "19":
                    ShowScoreOfAMatch();
                    break;
                default:
                    System.Console.WriteLine("Invalid input");
                    break;
            }
        }
        
    }
}

