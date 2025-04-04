using lab11.exception;

namespace lab11.domain.validator;

public class MatchValidator : IValidator<Match>
{
    private readonly TeamValidator _teamValidator = new TeamValidator();

    public bool Validate(Match match)
    {
        var error = new List<string>();

        try
        {
            _teamValidator.Validate(match.FirstTeam);
        }
        catch (ValidationException ex)
        {
            error.Add(ex.Message);
        }
        
        try
        {
            _teamValidator.Validate(match.SecondTeam);
        }
        catch (ValidationException ex)
        {
            error.Add(ex.Message);
        }

        if (error.Count != 0)
        {
            error.Insert(0, "Match is invalid");
            throw new ValidationException(string.Join('\n', error));
        }
        return true;
    }
}