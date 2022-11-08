/*
Read two integers and compute their sum, average and sum of the squares of the numbers.
*/

#include <stdio.h>

int main()
{
    int a, b;
    printf("Introduceti numerele ");
    scanf("%d%d", &a, &b);
    
    int suma;
    suma=a+b;
    printf("\nSuma numerelor este %d", suma);
    
    int suma_patrate;
    suma_patrate=a*a+b*b;
    printf("\nSuma patratelor este %d", suma_patrate);
    
    float medie;
    medie=(float)(a+b)/2;
    printf("\nMedia numerelor este %.2f", medie);
    
    return 0;
}