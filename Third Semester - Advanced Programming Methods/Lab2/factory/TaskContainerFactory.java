package factory;

import model.Container;
import model.QueueContainer;
import model.StackContainer;

public class TaskContainerFactory implements Factory{
    private static TaskContainerFactory instance = null ;

    private TaskContainerFactory() {}

    public static TaskContainerFactory getInstance() {
        if(instance == null) {
            instance = new TaskContainerFactory();
        }
        return instance;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        return switch (strategy){
            case FIFO -> new QueueContainer();
            case LIFO -> new StackContainer();
            default -> throw new IllegalArgumentException("Invalid strategy");
        };
    }
}
