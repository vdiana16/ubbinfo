package sort;

public class MergeSort extends AbstractSorter {
    @Override
    public void sort(int[] array){
        mergeSort(array, 0, array.length - 1);
    }

    private static void mergeSort(int[] array, int left, int right){
        if(left < right){
            int middle = (left + right) / 2;
            mergeSort(array, left, middle);
            mergeSort(array, middle + 1, right);
            merge(array, left, right);
        }
    }

    private static void merge(int[] array, int left, int right){
        int middle = (left + right) / 2;
        int lenLeft = middle - left + 1;
        int lenRight = right - middle;

        int[] tempLeft = new int[lenLeft];
        int[] tempRight = new int[lenRight];

        for(int i = 0; i < lenLeft; i++){
            tempLeft[i] = array[left + i];
        }
        for(int i = 0; i < lenRight; i++){
            tempRight[i] = array[middle + i + 1];
        }
        int i = 0, j = 0, k = left;
        while(i < lenLeft && j < lenRight){
            if(tempLeft[i] < tempRight[j]){
                array[k++] = tempLeft[i];
                i++;
            }
            else
            {
                array[k++] = tempRight[j];
                j++;
            }
        }
        while(i < lenLeft){
            array[k++] = tempLeft[i++];
        }
        while(j < lenRight){
            array[k++] = tempRight[j++];
        }
    }
}
