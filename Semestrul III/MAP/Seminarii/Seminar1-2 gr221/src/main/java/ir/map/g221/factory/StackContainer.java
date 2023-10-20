package ir.map.g221.factory;

import ir.map.g221.domain.Task;

import java.util.ArrayList;
import java.util.List;

public class StackContainer implements Container {
    private List<Task> list;

    public StackContainer() {
        list = new ArrayList<>();
    }

    @Override
    public Task remove() {
        // TODO test if the list is empty
        return list.remove(list.size() - 1);
    }

    @Override
    public void add(Task task) {
        list.add(task);
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }
}
