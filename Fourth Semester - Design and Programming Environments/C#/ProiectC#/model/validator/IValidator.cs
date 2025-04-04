namespace TravelAgency.model.validator;

public interface IValidator<T>
{
    bool Validate(T value);
}