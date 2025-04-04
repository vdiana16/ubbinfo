using System.ComponentModel.DataAnnotations;
using ValidationException = lab11.exception.ValidationException;

namespace lab11.domain.validator;

public class PlayerValidator : StudentValidator
{
    public bool ValidateTeam(Team team)
    {
        try
        {
            var teamValidator = new TeamValidator();
            teamValidator.Validate(team);
        }
        catch (ValidationException e)
        {
            var error = e.Message.Insert(0, "Player's team is invalid.");
            throw new ValidationException(string.Join('\n', error));
        }
        return true;
    }

    public override bool Validate(Student student)
    {
        if(student is not Player player)
            throw new ValidationException("Student is not a player");
        
        var errors = new List<string>();

        try
        {
            base.Validate(student);
        }
        catch (ValidationException e)
        {
            errors.Add(e.Message);
        }

        try
        {
            ValidateTeam(player.Team);
        }
        catch (ValidationException e)
        {
            errors.Add(e.Message);
        }

        if (errors.Count != 0)
        {
            errors.Insert(0, "Player is invalid.");
            throw new ValidationException(string.Join('\n', errors));
        }
        return true;
    }
}