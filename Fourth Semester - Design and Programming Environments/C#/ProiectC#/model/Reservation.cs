namespace TravelAgency.model;

public class Reservation : Entity<int>
{
    private Trip _trip;
    private String _clientName;
    private String _clientContact;
    private int _numberOfReservedSeats;

    public Reservation(Trip trip, String clientName, String clientContact, int numberOfReservedSeats)
    {
        _trip = trip;
        _clientName = clientName;
        _clientContact = clientContact;
        _numberOfReservedSeats = numberOfReservedSeats;
    }

    public Trip Trip => _trip;

    public String ClientName
    {
        get => _clientName;
        set => _clientName = value;
    }

    public String ClientContact
    {
        get => _clientContact;
        set => _clientContact = value;
    }

    public int NumberOfReservedSeats
    {
        get => _numberOfReservedSeats;
        set => _numberOfReservedSeats = value;
    }

    public override string ToString()
    {
        return _trip.ToString() + $"Client Name: {_clientName}, Client Contact: {_clientContact}, Number of Reserved Seats: {_numberOfReservedSeats}";
    }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;
        Reservation other = (Reservation)obj;
        return _trip == other._trip && _clientContact == other._clientContact && _clientName == other._clientName && 
               _numberOfReservedSeats == other._numberOfReservedSeats;

    }

    public override int GetHashCode()
    {
        return HashCode.Combine(_trip, _clientName, _clientContact, _numberOfReservedSeats);
    }
}