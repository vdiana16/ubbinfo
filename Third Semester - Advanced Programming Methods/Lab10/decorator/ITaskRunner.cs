namespace lab10.decorator;


using Task = lab10.model.Task;
public interface ITaskRunner
{
    void ExecuteOneTask();
    
    void ExecuteAllTasks();
    
    void AddTask(Task task);
    
    bool HasTask();
}