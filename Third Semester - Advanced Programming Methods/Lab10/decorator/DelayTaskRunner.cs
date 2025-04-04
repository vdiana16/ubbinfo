using lab10.model;

namespace lab10.decorator;

public class DelayTaskRunner: AbstractTaskRunner
{
    public DelayTaskRunner(ITaskRunner taskRunner): base(taskRunner)
    {
        
    }

    public override void ExecuteOneTask()
    {
        try
        {
            Console.WriteLine("Waiting for task to finish...");
            Thread.Sleep(3000);
        }
        catch (ThreadInterruptedException)
        {
            throw new Exception("The task runner is interrupted.");
        }
        base.ExecuteOneTask();
    }
}