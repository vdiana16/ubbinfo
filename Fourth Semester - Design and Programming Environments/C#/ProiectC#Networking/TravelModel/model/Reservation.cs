namespace TravelModel.model;

public class Reservation : Entity<int>
{
    private Tour _tour;
    private String _clientName;
    private String _clientContact;
    private int _numberOfReservedSeats;

    public Reservation(Tour tour, String clientName, String clientContact, int numberOfReservedSeats)
    {
        _tour = tour;
        _clientName = clientName;
        _clientContact = clientContact;
        _numberOfReservedSeats = numberOfReservedSeats;
    }

    public Tour Tour => _tour;

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
        return _tour.ToString() + $"Client Name: {_clientName}, Client Contact: {_clientContact}, Number of Reserved Seats: {_numberOfReservedSeats}";
    }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;
        Reservation other = (Reservation)obj;
        return _tour == other._tour && _clientContact == other._clientContact && _clientName == other._clientName && 
               _numberOfReservedSeats == other._numberOfReservedSeats;

    }

    public override int GetHashCode()
    {
        return HashCode.Combine(_tour, _clientName, _clientContact, _numberOfReservedSeats);
    }
}