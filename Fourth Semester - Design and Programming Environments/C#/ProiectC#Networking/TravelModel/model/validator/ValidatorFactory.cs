namespace TravelModel.model.validator;

public class ValidatorFactory
{
    private static ValidatorFactory _instance;
    
    private ValidatorFactory() { }

    public static ValidatorFactory GetInstance()
    {
        return _instance ??= new ValidatorFactory();
    }

    public IValidator<T> CreateValidator<T>(ValidatorStrategy strategy)
    {
        return strategy switch
        {
            ValidatorStrategy.Agent => new AgentValidator() as IValidator<T>,
            ValidatorStrategy.Reservation => new ReservationValidator() as IValidator<T>,
            ValidatorStrategy.Tour => new TourValidator() as IValidator<T>,
            _ => throw new NotImplementedException()
        };
    }
}