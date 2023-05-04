#include <fstream>
#include <iostream>
using namespace std;
ifstream f("in.txt");
int n, nr, nod1, nod2, valoare;
int matPond[105][105], matAd[105][105], rf[105][105], grNoduri[105], c[105], viz[105];
int main()
{
    f>>n>>nr;
    int x=n;
    for(int i=1; i<=nr; i++)
    {   for(int j=1; j<=nr; j++)
        {   matPond[i][j]=-1;
            rf[i][j]=10000;
        }
        matPond[i][i]=0;
        rf[i][i]=0;
    }

    while(x)
    {   f>>nod1>>nod2>>valoare;
        matPond[nod1][nod2]=matPond[nod2][nod1]=valoare;
        matAd[nod1][nod2]=matAd[nod2][nod1]=rf[nod1][nod2]=rf[nod2][nod1]=1;
        x--;
    }


    cout<<"1. Noduri izolate\n";
    for(int i=1; i<=nr; i++)
    {   int w=0;
        for(int j=1; j<=nr; j++)
            if(matPond[i][j]>0) w=1;
        if(w==0) cout<<i<<" ";
    }

    cout<<"\n\n2. Este graful regular?\n";
    for(int i=1; i<=nr; i++)
        for(int j=1; j<=nr; j++)
            if(matPond[i][j]>0)
                grNoduri[i]++;

    int w=1;
    for(int i=2; i<=nr; i++)
        if(grNoduri[i]!=grNoduri[i-1]) w=0;
    if(w==1) cout<<"DA\n";
    else cout<<"NU\n";

    cout<<"\n3. Matricea ponderilor (considerand -1 = oo)\n\n";
    for(int i=1; i<=nr; i++)
    {   for(int j=1; j<=nr; j++)
            cout<<matPond[i][j]<<" ";
        cout<<'\n';
    }

    cout<<"\n4. Transformarea din matricea de adiacenta in matricea distantelor\n\n";

    for(int k=1; k<=nr; k++)
        for(int i=1; i<=nr; i++)
            for(int j=1; j<=nr; j++)
                if(i!=j)
                    if(rf[i][j]>rf[i][k]+rf[k][j])
                        rf[i][j]=rf[i][k]+rf[k][j];

    for(int i=1; i<=nr; i++)
    {   for(int j=1; j<=nr; j++)
            cout<<rf[i][j]<<" ";
        cout<<"\n";
    }

    cout<<"\n5. Este graful conex?\n";

    int p,u,y;
    c[1]=1; viz[1]=1; p=u=1;
    while(p<=u)
    {   y=c[p];
        for(int j=1;j<=n;j++)
            if(matAd[y][j] and !viz[j]) {viz[j]=1; c[++u]=j;}
        p++;
    }
    if(u==nr) cout<<"DA\n"; else cout<<"NU\n";

    return 0;
}
