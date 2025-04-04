namespace lab11.domain;

public class Team : Entity<int>
{
    public string Name {get; set;}

    public Team() { }

    public Team(string name)
    {
        Name = name;
    }

    public override string ToString()
    {
        return base.Id.ToString() + " " + Name;
    }
}