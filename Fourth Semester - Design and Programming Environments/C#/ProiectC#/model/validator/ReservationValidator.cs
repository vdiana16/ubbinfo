namespace TravelAgency.model.validator;

using TravelAgency.exception;

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
        
        if (entity.Trip == null)
        {
            throw new ValidationException("Trip cannot be empty");
        }
        
        if (entity.NumberOfReservedSeats == null)
        {
            throw new ValidationException("Number Of Reserved Seats cannot be empty");
        }
        return true;
    }
}