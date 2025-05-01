namespace TravelModel.model.validator;
public class TourValidator: IValidator<Tour>
{
    public bool Validate(Tour entity)
    {
        if (entity == null)
        {
            throw new ArgumentNullException(nameof(entity), "Tour cannot be null");
        }

        if (string.IsNullOrEmpty(entity.Destination))
        {
            throw new ValidationException("Destination cannot be empty");
        }

        if (string.IsNullOrEmpty(entity.TransportCompany))
        {
            throw new ValidationException("TransportCompany cannot be empty");
        }
        
        if (entity.DepartureDate == null)
        {
            throw new ValidationException("Departure Date cannot be empty");
        }

        if (entity.NumberOfAvailableSeats == null)
        {
            throw new ValidationException("Number Of Available Seats cannot be empty");
        }

        if (entity.Price == null)
        {
            throw new ValidationException("Price cannot be empty");

        }
        return true;
    }
}