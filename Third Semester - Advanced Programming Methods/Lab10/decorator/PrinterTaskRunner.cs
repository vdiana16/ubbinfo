namespace lab10.decorator;

public class PrinterTaskRunner: AbstractTaskRunner
{
    private static readonly string dateFormat = "yyyy-MM-dd HH:mm";
    
    public PrinterTaskRunner(ITaskRunner taskRunner): base(taskRunner)
    {
        
    }

    public override void ExecuteOneTask()
    {
        base.ExecuteOneTask();
        Console.WriteLine("The task is finished at: " + DateTime.Now.ToString(dateFormat));
    }
}