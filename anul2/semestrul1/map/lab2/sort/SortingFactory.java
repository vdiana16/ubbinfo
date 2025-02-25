package sort;

public class SortingFactory implements SortingInterface {
    private static SortingFactory instance = null;

    private SortingFactory() {}

    public static SortingFactory getInstance() {
        if (instance == null) {
            instance = new SortingFactory();
        }
        return instance;
    }

    @Override
    public AbstractSorter makeSorter(SortingStrategy strategy) {
        return switch (strategy){
            case BubbleSort -> new BubbleSort();
            case MergeSort -> new MergeSort();
            default -> throw new IllegalArgumentException("Unsupported SortingStrategy");
        };
    }
}
