namespace TravelAgency.utils;

public interface IObserver<T>
{
    void Update(T eventData);
}