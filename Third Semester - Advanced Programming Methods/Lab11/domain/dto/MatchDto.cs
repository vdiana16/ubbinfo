namespace lab11.domain.dto;

public class MatchDto : Entity<int>
{
    public int IdFirstTeam { get; set; }
    public int IdSecondTeam { get; set; }
    public DateTime MatchDate { get; set; }

    public MatchDto() { }

    public override string ToString()
    {
        return $"{Id},{IdFirstTeam},{IdSecondTeam},{MatchDate.ToString(Match.Date_Format)}";
    }
}