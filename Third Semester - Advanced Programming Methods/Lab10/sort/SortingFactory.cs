namespace lab10.sort;

public class SortingFactory: SortingInterface
{
    private static SortingFactory _instance = null;
    
    private SortingFactory() { }

    public static SortingFactory Instance => _instance ??= new SortingFactory();

    public AbstractSorter makeSorter(SortingStrategy strategy)
    {
        switch (strategy)
        {
            case SortingStrategy.BubbleSort: return new BubbleSort();
            case SortingStrategy.MergeSort: return new MergeSort();
            default: return null;
        }
    }
}