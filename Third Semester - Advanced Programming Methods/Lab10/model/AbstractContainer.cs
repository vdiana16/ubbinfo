namespace lab10.model;

public abstract class AbstractContainer:IContainer
{
    protected List<Task> tasks = new List<Task>();

    public abstract Task Remove();

    public void Add(Task task)
    {
        tasks.Add(task);
    }

    public int Size()
    {
        return tasks.Count;
    }

    public bool IsEmpty()
    {
        return tasks.Count == 0;
    }

    public List<Task> Container
    {
        get;
        set;
    }
}