namespace lab10.sort;

public class BubbleSort: AbstractSorter
{
    public override void sort(int[] array)
    {
        int n = array.Length;
        bool sorted;
        do
        {
            sorted = true;
            for (int i = 0; i < n - 1; i++)
            {
                if (array[i] > array[i + 1])
                {
                    swap(array, i, i + 1);
                    sorted = false;
                }
            }
        }while(!sorted);
    }
}