package ir.map.g221.factory;

import ir.map.g221.domain.Task;

public class StackContainer extends AbstractContainer {

    public StackContainer() {
        super();
    }

    @Override
    public Task remove() {
        // TODO test if the list is empty
        return list.remove(list.size() - 1);
    }

}
