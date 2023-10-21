package ir.map.g221.domain;

public class QuickSort extends AbstractSort{

    public QuickSort(){}

    @Override
    public void sort(int[] vector) {
        quickSort(vector, 0, vector.length-1);
    }

    private void quickSort(int[] vector, int i, int i1) {
        if(i<i1){
            int pivotIndex = partition(vector, i, i1);

            quickSort(vector, i, pivotIndex-1);
            quickSort(vector, pivotIndex+1, i1);
        }
    }

    private int partition(int[] vector, int i, int i1) {
        int pivot = vector[i1];
        int j = (i-1);

        for(int l=i; j<i1; j++){
            if(vector[j]<pivot){
                j++;
                swap(vector, j, l);
            }
        }
        swap(vector, j+1, i1);
        return j+1;
    }

    private void swap(int[] vector, int j, int l) {
        int aux = vector[j];
        vector[j]=vector[l];
        vector[l] = aux;
    }
}
