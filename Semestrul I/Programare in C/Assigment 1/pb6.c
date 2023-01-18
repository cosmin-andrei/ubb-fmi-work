/*Given the natural number h and m, 
that represent the current time expressed inhours and minutes, 
compute the time after x hours and y minutes.
*/

#include <stdio.h>

int main()
{
    int h,m;
    printf("introdu ora si minutul: ");
    scanf("%d%d", &h, &m);
    
    int x,y;
    printf("\n introdu dupa cate ore si minute sa apara timpul: ");
    scanf("%d%d", &x, &y);
    
    while(y)
    {
        if(y>=60)
        {
            h=h+1;
            y=y-60;
        }
        else if(m+y>60)
        {
            h=h+1;
            m=(m+y)-60;
            break;
        }
        else
        {
            m=m+y;
            break;
        }
    }
    
    h=h+x;
    
    if(y==60)
    { y=0;
      h=h+1;
    }
    
    
    printf("\n Ora %d", h);
    printf(" Minutul %d", m);
    
    return 0;
}