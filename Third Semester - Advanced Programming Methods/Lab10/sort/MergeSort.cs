namespace lab10.sort;

public class MergeSort: AbstractSorter
{
    public override void sort(int[] array)
    {
        merge(array, 0, array.Length - 1);
    }
    
    private static void mergeSort(int[] array, int left, int right)
    {
        if (left < right)
        {
            int middle = (left + right) / 2;
            mergeSort(array, left, middle);
            mergeSort(array, middle + 1, right);
            merge(array, left, right);
        }
    }

    private static void merge(int[] array, int left, int right)
    {
        int i, j;
        
        int middle = left + (right + left) / 2;
        int lenLeft = middle - left + 1;
        int lenRight = right - middle;
        
        int[] leftArray = new int[lenLeft];
        int[] rightArray = new int[lenRight];

        for (i = 0; i < lenLeft; i++)
        {
            leftArray[i] = array[left + i];
        }

        for (i = 0; i < lenRight; i++)
        {
            rightArray[i] = array[middle + i + 1];
        }

        i = 0;
        j = 0;
        int k = left;
        while (i < lenLeft && j < lenRight)
        {
            if (leftArray[i] < rightArray[j])
            {
                array[k++] = leftArray[i++];
            }
            else
            {
                array[k++] = rightArray[j++];
            }
        }

        while (i < lenLeft)
        {
            array[k++] = leftArray[i++];
        }

        while (j < lenRight)
        {
            array[k++] = rightArray[j++];
        }
    }
}