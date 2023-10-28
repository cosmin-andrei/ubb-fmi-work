package ir.map.g221.domain;

import ir.map.g221.factory.SorterFactory;
import ir.map.g221.factory.Strategy;

import java.util.Arrays;

public class SortingTask  extends Task{

    protected int[] numere;
    protected AbstractSort sorter;

    public SortingTask(int[] numere, Strategy strategy)
    {
        this.numere = numere;
        //strategia de sortare
        this.sorter = SorterFactory.getInstance().createSorter(strategy);
    }

    //suprascrisa din clasa Task pt sortare
    @Override
    public void run() {
        sorter.sort(this.numere);
    }

    @Override
    public String toString() {

        String s = "";
        for(int i=0; i<this.numere.length-1; i++)
            s = s+this.numere[i]+" ";

        s = s+this.numere[this.numere.length-1];

        return s;
    }
}
