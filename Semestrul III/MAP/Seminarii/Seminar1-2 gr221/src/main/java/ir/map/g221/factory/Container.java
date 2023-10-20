package ir.map.g221.factory;

import ir.map.g221.domain.Task;

public interface Container {
    Task remove();
    void add(Task task);
    int size();
    boolean isEmpty();
}
