package ir.map.g221.factory;

public class TaskContainerFactory implements Factory {

    private static TaskContainerFactory instance = null;

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

    public static TaskContainerFactory getInstance(){
        if(instance == null){
            instance = new TaskContainerFactory();
        }
        return instance;
    }
}
