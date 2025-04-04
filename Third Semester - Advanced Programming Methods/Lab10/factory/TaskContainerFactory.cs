using lab10.model;

namespace lab10.factory;

public class TaskContainerFactory: IFactory
{
    private static TaskContainerFactory _instance;
    
    private TaskContainerFactory() { }
    
    public static TaskContainerFactory Instance => _instance ??= new TaskContainerFactory();
    
    public IContainer createContainer(Strategy startegy)
    {
        switch (startegy)
        {
            case Strategy.LIFO: return new StackContainer();
            case Strategy.FIFO: return new QueueContainer();
            default: throw new ArgumentException("Invalid strategy");
        }
    }
}