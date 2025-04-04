namespace lab10.model;

public class QueueContainer:AbstractContainer
{
    public QueueContainer() : base()
    {
        
    }

    public override Task Remove()
    {
        Task taskRemoved = tasks.First();
        tasks.Remove(taskRemoved);
        return taskRemoved;
    }
}