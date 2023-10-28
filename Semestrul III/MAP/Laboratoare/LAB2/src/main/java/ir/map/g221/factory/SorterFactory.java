package ir.map.g221.factory;

import ir.map.g221.domain.AbstractSort;
import ir.map.g221.domain.BubbleSort;
import ir.map.g221.domain.QuickSort;

public class SorterFactory {

    //asigura unicitatea instantei pe intreg programul
    static SorterFactory instance = null;

    //implementarea sortarii dupa o strategie
    public AbstractSort createSorter(Strategy strategy) {
        if (Strategy.BUBBLE_SORT == strategy)
            return new BubbleSort();
        else
            return new QuickSort();
    }

    public static SorterFactory getInstance() {
        if (instance == null)
            instance = new SorterFactory();
        return instance;
    }
}
