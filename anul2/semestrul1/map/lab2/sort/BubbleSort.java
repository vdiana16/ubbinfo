package sort;

public class BubbleSort extends AbstractSorter {
    @Override
    public void sort(int[] array) {
        int n = array.length;
        boolean sorted;
        do{
            sorted = true;
            for(int i = 0; i < n-1; i++){
                if(array[i] > array[i+1]){
                    swap(array, i, i+1);
                    sorted = false;
                }
            }
        }while(!sorted);
    }
}
