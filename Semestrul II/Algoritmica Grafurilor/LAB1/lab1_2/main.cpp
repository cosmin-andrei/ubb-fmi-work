#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("in.txt");

int main()
{
    int n, mat[20][20]= {0},a1,a2;
    fin>>n;

    while(fin>>a1>>a2)
    {
        mat[a1][a2]=1;
        mat[a2][a1]=1;
    }

    fin.close();

    ///noduri izolate
    cout<<"Nodurile izolate sunt: ";
    for(int i=1; i<=n; i++)
    {
        bool ok=true;
        for(int j=1; j<=n; j++)
            if(mat[i][j]==1) ok=false;

        if(ok) cout << i << " ";
    }
    cout<<endl;

    ///graf regulat

    bool ok=true;
    int kelem=0;
    for(int i=1; i<=n; i++)
        if(mat[1][i]==1) kelem++;
    for(int i=1; i<=n && ok==true; i++)
    {
        int k=0;

        for(int j=1; j<=n; j++)
            if(mat[i][j]==1) k++;

        if(k!=kelem) ok=false;
    }

    if(ok==true) cout<<"graf regulat";
    else cout<<"graf neregulat";
    cout<<endl;

    ///matrice adiacenta -> matrice distante
    int inf=INT_MAX;
    int d[21][21];
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(mat[i][j]!=0) d[i][j]=mat[i][j];
            else d[i][j]=inf;

    //aplicam algoritmul Floyd-Warshall

    for (int k=1; k<=n; k++)
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                if (d[i][k]!=inf && d[k][j]!=inf && d[i][k]+d[k][j]<d[i][j])
                    d[i][j]=d[i][k]+d[k][j];


    for(int i=1; i<=n; i++)
    {
        cout<<endl;
        for(int j=1; j<=n; j++)
            cout<<d[i][j]<<" ";
    }

    cout<<endl;

    ///graf conex

    ok=true;
    for(int i=1; i<=n && ok==true; i++)
    {
        int k=0;
        for(int j=1; j<=n; j++)
            if(mat[i][j]==0) k++;

        if(k>1) ok=false;

    }

    if(ok==true) cout<<"Graful este conex";
    else cout<<"Graful nu este conex";


    return 0;
}
