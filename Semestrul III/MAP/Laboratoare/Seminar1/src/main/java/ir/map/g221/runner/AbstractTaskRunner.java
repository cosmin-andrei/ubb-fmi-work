package ir.map.g221.runner;


import ir.map.g221.domain.Task;

public abstract class AbstractTaskRunner implements TaskRunner {
    protected TaskRunner tr;

    public AbstractTaskRunner(TaskRunner tr) {
        this.tr = tr;
    }

    @Override
    public void executeOneTask() {
        tr.executeOneTask();
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
            tr.executeAll();
    }

    @Override
    public void addTask(Task t) {
        tr.addTask(t);
    }

    @Override
    public boolean hasTask() {
        return tr.hasTask();
    }
}
