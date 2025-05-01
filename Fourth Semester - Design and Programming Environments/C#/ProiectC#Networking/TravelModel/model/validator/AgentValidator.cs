namespace TravelModel.model.validator;

public class AgentValidator : IValidator<Agent>
{
    public bool Validate(Agent entity)
    {
        if (entity == null)
        {
            throw new ArgumentNullException(nameof(entity), "Agency cannot be null");
        }

        if (string.IsNullOrEmpty(entity.Name))
        {
            throw new ValidationException("Agent name cannot be empty");
        }

        if (string.IsNullOrEmpty(entity.Username))
        {
            throw new ValidationException("Agency username cannot be empty");
        }

        if (string.IsNullOrEmpty(entity.Password))
        {
            throw new ValidationException("Agency password cannot be empty");
        }
        
        return true;
    }
}