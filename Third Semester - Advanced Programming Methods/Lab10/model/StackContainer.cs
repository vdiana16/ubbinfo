namespace lab10.model;

public class StackContainer:AbstractContainer
{
    public StackContainer() : base()
    {
        
    }
    
    public override Task Remove()
    {
        Task taskRemoved = tasks[^1];
        tasks.Remove(taskRemoved);
        return taskRemoved;
    }
}