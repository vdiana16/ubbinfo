namespace lab11.domain.dto;

public class PlayerDto : Entity<int>
{
    public int IdStudent { get; set; }
    public int IdTeam { get; set; }
    
    public PlayerDto(){ }

    public override string ToString()
    {
        return $"{Id},{IdStudent},{IdTeam}";
    }
}