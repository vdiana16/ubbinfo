namespace lab11.domain.validator;

public interface IValidator<T>
{
    bool Validate(T value);
}