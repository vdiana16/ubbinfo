namespace lab10.model;

public abstract class Task
{
    private string _taskId;
    private string _description;

    public Task(string taskId, string description)
    {
        this._taskId = taskId;
        this._description = description;
    }
    
    public string TaskID { get => _taskId; set => _taskId = value; }
    
    public string Description { get => _description; set => _description = value; }
    
    public override string ToString()
    {
        return $"Task: {_description}\nTaskID: {_taskId}";
    }

    public override bool Equals(object? obj)
    {
        if (this == obj)
            return true;
        if (obj == null || GetType() != obj.GetType())
            return false;

        Task task = (Task)obj;
        return Equals(_taskId, task._taskId) && Equals(_description, task._description);

    }

    public override int GetHashCode()
    {
        return HashCode.Combine(_taskId, _description);
    }

    public abstract void execute();
}