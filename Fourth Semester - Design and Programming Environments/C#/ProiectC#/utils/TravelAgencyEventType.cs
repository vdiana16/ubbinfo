namespace TravelAgency.utils;

public class TravelAgencyEventType
{
    public ChangeEventType Type { get; }
    public object Data { get; }

    public TravelAgencyEventType(ChangeEventType type, object data)
    {
        Type = type;
        Data = data;
    }
}

public enum ChangeEventType
{
    RESERVEDSEAT,
    CANCELEDRESERVATION
}