package sort;

public abstract class AbstractSorter {
    public abstract void sort(int[] array);

    static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
