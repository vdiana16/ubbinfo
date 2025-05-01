namespace TravelModel.model.validator;

public interface IValidator<T>
{
    bool Validate(T value);
}