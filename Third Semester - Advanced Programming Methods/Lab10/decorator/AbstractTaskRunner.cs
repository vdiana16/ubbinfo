namespace lab10.decorator;

using Task = lab10.model.Task;
public class AbstractTaskRunner: ITaskRunner
{
    private readonly ITaskRunner _taskRunner;

    public AbstractTaskRunner(ITaskRunner taskRunner)
    {
        _taskRunner = taskRunner;
    }

    public virtual void ExecuteOneTask()
    {
        _taskRunner.ExecuteOneTask();
    }

    public virtual void ExecuteAllTasks()
    {
        while (HasTask())
        {
           ExecuteOneTask();
        }
    }

    public virtual void AddTask(Task task)
    {
        _taskRunner.AddTask(task);
    }

    public virtual bool HasTask()
    {
        return _taskRunner.HasTask();
    }
}