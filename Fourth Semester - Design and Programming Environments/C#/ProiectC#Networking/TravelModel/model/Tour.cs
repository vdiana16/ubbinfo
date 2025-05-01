namespace TravelModel.model;

public class Tour : Entity<int>
{
    private string _destination;
    private string _transportCompany;
    private DateTime _departureDate;
    private double _price;
    private int _numberOfAvailableSeats;

    public Tour(string destination, string transportCompany, DateTime departureDate, double price, int numberOfAvailableSeats)
    {
        _destination = destination;
        _transportCompany = transportCompany;
        _departureDate = departureDate;
        _price = price;
        _numberOfAvailableSeats = numberOfAvailableSeats;
    }

    public string Destination
    {
        get => _destination;
        set => _destination = value;
    }

    public string TransportCompany
    {
        get => _transportCompany;
        set => _transportCompany = value;
    }

    public DateTime DepartureDate
    {
        get => _departureDate;
        set => _departureDate = value;
    }

    public double Price
    {
        get => _price;
        set => _price = value;
    }

    public int NumberOfAvailableSeats
    {
        get => _numberOfAvailableSeats;
        set => _numberOfAvailableSeats = value;
    }
    
    public override string ToString()
    {
        return $"Destination: {_destination}, TransportCompany: {_transportCompany}, DepartureDate: {_departureDate}, " +
               $"Price: {_price}, NumberOfAvailableSeats: {_numberOfAvailableSeats}";
    }

    public override bool Equals(object? obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;
        Tour other = (Tour)obj;
        return _destination == other._destination && _transportCompany == other._transportCompany && _departureDate == other._departureDate
            && _price == other._price && _numberOfAvailableSeats == other._numberOfAvailableSeats;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(_destination, _transportCompany, _departureDate, _price, _numberOfAvailableSeats);
    }
    
}