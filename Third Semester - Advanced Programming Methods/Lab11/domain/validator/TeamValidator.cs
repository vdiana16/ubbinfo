using lab11.exception;

namespace lab11.domain.validator;

public class TeamValidator : IValidator<Team>
{
    public bool ValidateName(string name)
    {
        if (string.IsNullOrEmpty(name))
            throw new ValidationException("Team name cannot be empty");
        return true;
    }

    public bool Validate(Team team)
    {
        var error = new List<string>();

        try
        {
            ValidateName(team.Name);
        }
        catch (ValidationException e)
        {
            error.Add(e.Message);
        }

        if (error.Count != 0)
        {
            error.Insert(0, "Team is invalid!");
            throw new ValidationException(string.Join("\n", error));

        }
        return true;
    }
}