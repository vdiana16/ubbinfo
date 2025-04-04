namespace lab10.model;

public class MessageTask: Task
{
    private String message;
    private String from;
    private String to;
    private DateTime date;
    private static readonly string dateFormat = "yyyy-MM-dd HH:mm";

    public MessageTask(String taskId, String description, String message, String from, String to, DateTime date) : 
        base(taskId, description)
    {
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    public override string ToString()
    {
        return "id = " + TaskID +
               " | description = " + Description +
               " | message = " + message +
               " | from = " + from +
               " | to = " + to +
               " | date = " + date.ToString(dateFormat);

    }

    public override void execute()
    {
        Console.WriteLine(this.message + ": " + date.ToString(date + dateFormat));
    }
}