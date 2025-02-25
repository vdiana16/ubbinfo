package model;

import java.util.ArrayList;
import java.util.List;

public abstract class AbstractContainer implements Container {
    protected List<Task> tasks = new ArrayList<>();

    @Override
    public int size() {
        return tasks.size();
    }

    @Override
    public boolean isEmpty() {
        return tasks.isEmpty();
    }

    @Override
    public void add(Task task){
        tasks.add(task);
    }

    @Override
    //dar e clasa abstracta ce trebuie implementata de containere
    public abstract Task remove();
}
