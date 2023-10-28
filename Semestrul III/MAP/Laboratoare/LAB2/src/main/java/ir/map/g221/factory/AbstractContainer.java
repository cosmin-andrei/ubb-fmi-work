package ir.map.g221.factory;

import ir.map.g221.domain.Task;

import java.util.ArrayList;
import java.util.List;

public abstract class AbstractContainer implements Container{

    protected List<Task> list;
    protected int size;

    public AbstractContainer() {
        list = new ArrayList<>();
        this.size=0;
    }

    @Override
    public void add(Task task) {
        list.add(task);
        size++;
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