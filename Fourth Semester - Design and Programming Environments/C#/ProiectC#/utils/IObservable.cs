namespace TravelAgency.utils;

public interface IObservable<T>
{
    void AddObserver(IObserver<T> observer);
    void RemoveObserver(IObserver<T> observer);
    void NotifyObservers(T eventData);
}