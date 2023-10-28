package ir.map.g221.domain;

import jdk.jfr.Percentage;

public class BubbleSort extends AbstractSort {

    public BubbleSort(){}

    @Override
    public void sort(int[] numere){
        int i, j, aux;
        boolean swapped;
        int n = numere.length;

        for(i=0; i<n-1; i++) {
            swapped = false;
            for(j=0; j<n-i-1; j++){
                if(numere[j]>numere[j+1]){
                    aux=numere[j];
                    numere[j] = numere[j+1];
                    numere[j+1]=aux;
                    swapped=true;
                }
            }

            if(!swapped)
                break;
        }
    }
}
