namespace TravelModel.model.validator;

public class ReservationValidator: IValidator<Reservation>
{
    public bool Validate(Reservation entity)
    {
        if (entity == null)
        {
            throw new ArgumentNullException(nameof(entity), "Reservation cannot be null");
        }

        if (entity.ClientName == null)
        {
            throw new ValidationException("Client name cannot be empty");
        }
        
        if (entity.ClientContact == null)
        {
            throw new ValidationException("Client contact cannot be empty");
        }
        
        if (entity.Tour == null)
        {
            throw new ValidationException("Tour cannot be empty");
        }
        
        if (entity.NumberOfReservedSeats == null)
        {
            throw new ValidationException("Number Of Reserved Seats cannot be empty");
        }
        return true;
    }
}