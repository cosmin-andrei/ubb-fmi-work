package ir.map.g221.factory;

public class TaskContainerFactory implements Factory {
    @Override
    public Container createContainer(Strategy strategy) {
        if (strategy == Strategy.LIFO) {
            return new StackContainer();
        }
        else if (strategy == Strategy.FIFO) {
            return new QueueContainer();
        }
        else {
            return null;
        }
    }
}
