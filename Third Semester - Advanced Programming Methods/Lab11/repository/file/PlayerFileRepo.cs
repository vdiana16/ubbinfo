using lab11.domain.dto;

namespace lab11.repository.file;

public class PlayerFileRepo : InFileRepository<int, PlayerDto>
{
    public PlayerFileRepo(string filePath) : base(filePath, LineToPlayerDto, PlayerDtoToLine)
    {
        
    }

    public static PlayerDto LineToPlayerDto(string line)
    {
        var fields = line.Split(',');
        return new PlayerDto
        {
            Id = int.Parse(fields[0]),
            IdStudent = int.Parse(fields[1]),
            IdTeam = int.Parse(fields[2])
        };
    }

    public static string PlayerDtoToLine(PlayerDto playerDTO)
    {
        return playerDTO.ToString();
    }
}