using lab10.factory;
using lab10.model;
using Task = lab10.model.Task;
namespace lab10.decorator;

public class StrategyTaskRunner: ITaskRunner
{
    private readonly IContainer _container;

    public StrategyTaskRunner(Strategy strategy)
    {
        IFactory factory = TaskContainerFactory.Instance;
        _container = factory.createContainer(strategy);
    }

    public void ExecuteOneTask()
    {
        Task task = _container.Remove();
        task.execute();
    }

    public void ExecuteAllTasks()
    {
        while (HasTask())
        {
            ExecuteOneTask();
        }
    }

    public void AddTask(Task task)
    {
        _container.Add(task);
    }

    public bool HasTask()
    {
        return !_container.IsEmpty();
    }
}