namespace lab10.sort;

public interface SortingInterface
{
    AbstractSorter makeSorter(SortingStrategy strategy);
}