namespace lab11.domain;

public class Match : Entity<int>
{
    public static readonly string Date_Format = "dd/MM/yyyy HH:mm";

    public Team FirstTeam { get; set; }
    public Team SecondTeam { get; set; }
    public DateTime MatchDate { get; set; }

    public Match() { }

    public Match(Team firstTeam, Team secondTeam, DateTime matchDate)
    {
        FirstTeam = firstTeam;
        SecondTeam = secondTeam;
        MatchDate = matchDate;
    }

    public override string ToString()
    {
        return base.Id.ToString() + $". First team: {FirstTeam.Name}  Second team: {SecondTeam.Name}  Match date: {MatchDate.ToString(Date_Format)}";
    }
}