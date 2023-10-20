package ir.map.g221.runner;

import ir.map.g221.domain.Task;
import ir.map.g221.factory.Container;
import ir.map.g221.factory.Factory;
import ir.map.g221.factory.Strategy;
import ir.map.g221.factory.TaskContainerFactory;

public class StrategyTaskRunner implements TaskRunner{
    private Container container;

    public StrategyTaskRunner(Strategy strategy) {
        Factory factory = new TaskContainerFactory();
        container = factory.createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        if (hasTask()) {
            container.remove().run();
        }
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
