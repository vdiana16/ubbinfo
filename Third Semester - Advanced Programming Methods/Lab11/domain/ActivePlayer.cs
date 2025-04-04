namespace lab11.domain;

public enum Type
{
    Scrub, Participant
}

public class ActivePlayer : Entity<int>
{
    public int IdPlayer { get; set; }

    public int IdMatch { get; set; }

    public int NumberOfPointsEntered { get; set; }

    public Type? Type { get; set; }

    public ActivePlayer()
    {
    }

    public ActivePlayer(int idPlayer, int idMatch, int numberOfPointsEntered, Type type)
    {
        IdPlayer = idPlayer;
        IdMatch = idMatch;
        NumberOfPointsEntered = numberOfPointsEntered;
        Type = type;
    }
}