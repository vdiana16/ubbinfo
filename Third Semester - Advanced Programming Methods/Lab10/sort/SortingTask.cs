namespace lab10.sort;
using Task = lab10.model.Task;
public class SortingTask: Task 
{
    private int[] _array;
    private SortingStrategy _sortingStrategy;
    private AbstractSorter _abstractSorter;

    public SortingTask(String taskID, String description, SortingStrategy sortingStrategy, int[] array): base(taskID, description)
    {
        this._array = array;
        this._sortingStrategy = sortingStrategy;
        SortingFactory factory = SortingFactory.Instance;
        this._abstractSorter = factory.makeSorter(sortingStrategy);
    }

    public override void execute()
    {
        _abstractSorter.sort(_array);
    }
}