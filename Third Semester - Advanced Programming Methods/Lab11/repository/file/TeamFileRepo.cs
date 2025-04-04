using lab11.domain;

namespace lab11.repository.file;

public class TeamFileRepo : InFileRepository<int, Team>
{
    public TeamFileRepo(string filePath) : base(filePath, LineToTeam, TeamToLine)
    {
        
    }

    public static Team LineToTeam(string line)
    {
        var fields = line.Split(',');
        return new Team
        {
            Id = int.Parse(fields[0]),
            Name = fields[1]
        };
    }

    public static string TeamToLine(Team team)
    {
        return $"{team.Id},{team.Name}";
    }
}