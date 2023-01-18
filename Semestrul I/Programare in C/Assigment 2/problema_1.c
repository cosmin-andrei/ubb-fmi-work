#include <stdio.h>
int main()
{
    int minim, maxim, nr;
    
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
    
    printf("Maximul este %d\n", minim);
    printf("Minimul este %d\n", maxim);
    
    return 0;
    
}