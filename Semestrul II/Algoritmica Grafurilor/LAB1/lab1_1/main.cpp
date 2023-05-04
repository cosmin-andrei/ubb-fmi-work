#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("in.txt");
int mat[20][20];

int main()
{
    int n,a1,a2;
    fin>>n;

    while(!fin.eof())
    {

        fin>>a1>>a2;
        mat[a1][a2]=1;
        mat[a2][a1]=1;

    }

    fin.close();

    ///matrice adiacenta
    for(int i=1; i<=n; i++)
    {
        cout<<endl;
        for(int j=1; j<=n; j++)
            cout<<mat[i][j]<<" ";
    }
    cout<<endl;

    ///mat adiacenta -> lista adiacenta
    int list_ad[20][20]= {0};
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {

            if(mat[i][j]==1)
            {
                int k=1;
                while(list_ad[i][k]!=0)
                    k++;
                list_ad[i][k]=j;

            }
        }

    for(int i=1; i<=n; i++)
    {
        if(list_ad[i][1]==0)
            cout<<i<<": nod izolat"<<endl;
        else
        {
            cout<<i<<": ";
            for(int j=1; j<n; j++)
                if(list_ad[i][j]!=0)
                    cout<<list_ad[i][j]<<" ";
                else break;
            cout<<endl;
        }
    }

    ///lista adiacenta -> matricea de incidenta
    int muchii[20][3]= {0};
    int km=1;
    for(int i=1; i<=n; i++)
        for(int j=1; j<n-1; j++)
            if(list_ad[i][j]>i) j++;
            else
            {
                muchii[km][1]=i;
                muchii[km][2]=list_ad[i][j];
                km=km+1;
            }

    int mat_in[20][20]= {0};
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(muchii[j][1]==i || muchii[j][2]==i)
                mat_in[i][j]=1;


    for(int i=1; i<=n; i++)
    {
        cout<<endl;
        for(int j=1; j<=n; j++)
            cout<<mat_in[i][j]<<" ";
    }

    cout<<endl;

    ///incidenta -> lista de adiacenta

    int lista_ad2[20][19]= {0};
    for(int j=1; j<=n; j++)
    {
        int nod1=-1, nod2;
        for(int i=1; i<=n; i++)
            if(mat_in[i][j]==1)
            {
                if(nod1==-1)
                    nod1=i;
                else nod2=i;
            }

        int k=1;
        while(lista_ad2[nod1][k]!=0)
            k++;
        lista_ad2[nod1][k]=nod2;

        k=1;
        while(lista_ad2[nod2][k]!=0)
            k++;
        lista_ad2[nod2][k]=nod1;
    }


    for(int i=1; i<=n; i++)
    {
        if(lista_ad2[i][1]==0)
            cout<<i<<": nod izolat"<<endl;
        else
        {
            cout<<i<<": ";
            for(int j=1; j<n; j++)
                if(lista_ad2[i][j]!=0)
                    cout<<lista_ad2[i][j]<<" ";
                else break;
            cout<<endl;
        }
    }

    ///lista adiacenta -> matrice de adiacenta
    int matrice_ad_2[20][20]= {0};
    for(int i=1; i<=n; i++)
        for(int j=1; j<n; j++)
            if(lista_ad2[i][j]!=0) matrice_ad_2[i][lista_ad2[i][j]]=1;

    for(int i=1; i<=n; i++)
    {
        cout<<endl;
        for(int j=1; j<=n; j++)
            cout<<matrice_ad_2[i][j]<<" ";
    }

    ///mat adiacenta -> lista
    int lista[20][20]={0};
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {

            if(matrice_ad_2[i][j]==1)
            {
                int k=1;
                while(lista[i][k]!=0)
                    k++;
                lista[i][k]=j;

            }
        }

    for(int i=1; i<=n; i++)
    {
        if(lista[i][1]==0)
            cout<<i<<": nod izolat"<<endl;
        else
        {
            cout<<i<<": ";
            for(int j=1; j<n; j++)
                if(lista[i][j]!=0)
                    cout<<lista[i][j]<<" ";
                else break;
            cout<<endl;
        }
    }

    return 0;
}
