using System.Globalization;
using lab11.domain;
using lab11.domain.dto;

namespace lab11.repository.file;

public class MatchFileRepo : InFileRepository<int, MatchDto>
{
    public MatchFileRepo(string filePath) : base(filePath, LineToMatchDto, MatchDtoToLine)
    {
        
    }
    
    public static MatchDto LineToMatchDto(string line)
    {
        var fields = line.Split(',');
        return new MatchDto
        {
            Id = int.Parse(fields[0]),
            IdFirstTeam = int.Parse(fields[1]),
            IdSecondTeam = int.Parse(fields[2]),
            MatchDate = DateTime.ParseExact(fields[3], Match.Date_Format, CultureInfo.InvariantCulture)
        };
    }

    public static string MatchDtoToLine(MatchDto matchDTO)
    {
        return matchDTO.ToString();
    }
}