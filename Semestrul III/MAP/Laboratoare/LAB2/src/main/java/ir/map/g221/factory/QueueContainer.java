package ir.map.g221.factory;

import ir.map.g221.domain.Task;

public class QueueContainer extends AbstractContainer {
    @Override
    public Task remove() {
        if (!isEmpty()) {
            Task task = list.remove(0);
            size--;
            return task;
        }

        return null;
    }
}
