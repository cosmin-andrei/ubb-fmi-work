#include <iostream>
using namespace std;
int n, m, matAd[105][105], matTranz[105][105], viz[105];
void DFS(int nod)
{   viz[nod]=1;
    for(int j=1; j<=n; j++)
        if(matAd[nod][j]==1 and viz[j]!=1) DFS(j);
}
int main()
{   cout<<"Numarul de noduri: ";
    cin>>n;
    cout<<"Numarul de muchii: ";
    cin>>m;
    cout<<"Introduceti muchiile\n";
    for(int i=1; i<=m; i++)
    {   int x, y;
        cin>>x>>y;
        matAd[x][y]=1;
    }
    for(int k=1; k<=n; k++)
    {   for(int ind=1; ind<=n; ind++)
            viz[ind]=0;
        DFS(k);
        for(int i=1; i<=n; i++)
        {   if (i==k) continue;
            if (viz[i]) matTranz[k][i+1]=1;
        }
    }

    for(int i=1; i<=n; i++, cout<<'\n')
        for(int j=1; j<=n; j++, cout<<matTranz[i][j]<<" ");
    return 0;
}
