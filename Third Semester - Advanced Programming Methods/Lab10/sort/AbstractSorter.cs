namespace lab10.sort;

public abstract class AbstractSorter
{
    public abstract void sort(int[] array);

    public static void swap(int[] array, int a, int b)
    {
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
}