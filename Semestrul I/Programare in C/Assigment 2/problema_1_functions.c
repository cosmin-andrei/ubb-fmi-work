#include <stdio.h>

void function(int *maxim, int *minim)
{
    printf("Introdu numerele si apoi introdu ` pentru a terminat de citit:\n");
    scanf("%d", &maxim);
    
    minim = maxim;
    
    while(scanf("%d", &nr))
    {
        if(nr<minim)
            minim=nr;
        if(nr>maxim)
            maxim=nr;
    }
}

void print(int minim, int maxim)
{
    printf("Maximul este %d\n", minim);
    printf("Minimul este %d\n", maxim);
}

int main()
{
    int maxim, minim;
    function(maxim, minim);
    print(minim, maxim);
    
}