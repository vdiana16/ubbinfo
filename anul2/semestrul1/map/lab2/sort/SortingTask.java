package sort;

import model.Task;

public class SortingTask extends Task {
    private int[] array;
    private SortingStrategy strategy;
    private AbstractSorter taskSorter;

    public SortingTask(String taskID, String descriere, SortingStrategy strategy, int[] array) {
        super(taskID, descriere);
        this.strategy = strategy;
        this.array = array;
        //Obtin o instanta a fabricii de sortare si creez un sorter specific strategiei
        SortingFactory factory = SortingFactory.getInstance();
        this.taskSorter = factory.makeSorter(strategy);
    }

    @Override
    public void execute() {
        taskSorter.sort(array);
    }
}
