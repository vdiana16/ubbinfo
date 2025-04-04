package model;

import java.util.AbstractList;
import java.util.ArrayList;
import java.util.List;

public class QueueContainer extends AbstractContainer{
    public QueueContainer() {
        super();
    }

    @Override
    public Task remove() {
        if(!tasks.isEmpty()) {
                return tasks.removeFirst();
        }
        return null;
    }
}