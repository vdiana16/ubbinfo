using lab11.exception;

namespace lab11.domain.validator;

public class ActivePlayerValidator : IValidator<ActivePlayer>
{
    public bool ValidateIdPlayer(int idPlayer)
    {
        if (idPlayer < 1)
        {
            throw new ValidationException("Invalid idPlayer.");
        }
        return true;
    }

    public bool ValidateIdMatch(int idMatch)
    {
        if (idMatch < 1)
        {
            throw new ValidationException("Invalid idMatch.");
        }
        return true;
    }

    public bool ValidateNumberofPointsEntered(int numberofPointsEntered)
    {
        if (numberofPointsEntered < 0)
        {
            throw new ValidationException("Invalid number of points entered.");
        }
        return true;
    }

    public bool Validate(ActivePlayer activePlayer)
    {
        var errors = new List<string>();

        try
        {
            ValidateIdPlayer(activePlayer.IdPlayer);
        }
        catch (ValidationException ex)
        {
            errors.Add(ex.Message);
        }

        try
        {
            ValidateIdMatch(activePlayer.IdMatch);
        }
        catch (ValidationException ex)
        {
            errors.Add(ex.Message);
        }

        try
        {
            ValidateNumberofPointsEntered(activePlayer.NumberOfPointsEntered);
        }
        catch (ValidationException ex)
        {
            errors.Add(ex.Message);
        }

        if (errors.Any())
        {
            errors.Insert(0, "Active Player is invalid!");
            throw new ValidationException(string.Join("\n", errors));
        }
        return true;
    }
}