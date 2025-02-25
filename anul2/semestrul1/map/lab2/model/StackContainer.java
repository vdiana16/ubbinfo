package model;

import java.util.ArrayList;
import java.util.List;

public class StackContainer extends AbstractContainer {
    public StackContainer() {
        super();
    }

    @Override
    public Task remove() {
        if (!tasks.isEmpty()) {
            return tasks.removeLast();
        }
        return null;
    }
}