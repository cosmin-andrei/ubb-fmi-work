#include <fstream>
using namespace std;
ifstream f("intrare.in");
ofstream g("iesire.out");
int n, nod1, nod2;
int matAd[105][105], matInc[105][105], matInc2[105][105], listaVec[105][105];
int main()
{   f>>n;
    int x=n;
    int k=1;
    while(x)
    {   f>>nod1>>nod2;
        matAd[nod1][nod2]=matAd[nod2][nod1]=1;
        matInc[k][nod1]=matInc[k][nod2]=1;
        x--; k++;
    }

    ///Din matricea de adiacenta in matricea de incidenta
    k=0;

    g<<"Matricea de adiacenta\n";

    for(int i=1; i<=n; i++)
    {   for(int j=1; j<=n; j++)
            g<<matAd[i][j]<<" ";
        g<<endl;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (matAd[i][j]==1)
            {   k++;
                matAd[i][j]=matAd[j][i]=0;
                matInc2[k][j]=matInc2[k][i]=1;
            }

    g<<"\nMatricea de incidenta rezultata\n";

    for(int i=1; i<=n; i++)
    {   for(int j=1; j<=n; j++)
            g<<matInc2[i][j]<<" ";
        g<<endl;
    }

    ///Din matricea de incidenta in matrice de adiacenta

    g<<"\nMatricea de incidenta\n";

    for (int i=1; i<=n; i++)
    {   for(int j=1; j<=n; j++)
            g<<matInc[i][j]<<" ";
        g<<endl;
    }

    int nod1=0, nod2=0;
    for(int i=1; i<=n; i++)
    {   for(int j=1; j<=n; j++)
            if(matInc[i][j]==1)
            {   nod2=nod1;
                nod1=j;
            }
        matAd[nod1][nod2]=matAd[nod2][nod1]=1;
    }

    g<<"\nMatricea de adiacenta rezultata\n";

    for (int i=1; i<=n; i++)
    {   for(int j=1; j<=n; j++)
            g<<matAd[i][j]<<" ";
        g<<endl;
    }

    ///Din matrice de adiacenta in lista vecinilor

    for(int i=1; i<=n; i++)
    {   k=0;
        for(int j=1; j<=n; j++)
            if(matAd[i][j]==1)
                listaVec[i][++k]=j;
        listaVec[i][0]=k;
    }

    g<<"\nLista vecinilor rezultata din matricea de adiacenta\n";

    for(int i=1; i<=n; i++)
    {   g<<i<<": ";
        for(int j=1; j<=listaVec[i][0]; j++)
            g<<listaVec[i][j]<<" ";
        g<<endl;
    }

    return 0;
}
