//Implementati rutinele Prufer de codificare si decodificare a unui arbore.

#include <bits/stdc++.h>
using namespace std;
int v[105],fr[105],matAd[105][105],n,p,u;

void zero(){

    for(int i=1; i<=n+1; i++)
        fr[i]=0;

}

void reinit(){

    for(int i=p; i<=u; i++)
        fr[v[i]]++;

}

void codare() //decodare
{
    cin>>n;
    for(int i=1; i<=n; i++)
        {cin>>v[i]; fr[v[i]]++;}

    p=1; u=n;

    int count=n;
    while(count){

        int i=1;
        while(fr[i])i++;
        u++; v[u]=i;
        int j=v[p];
        p++;
        matAd[i][j]=matAd[j][i]=1;
        zero();
        reinit();
        count--;
    }

    cout<<endl<<"Codare Prufer, matrice de adiacenta: "<<endl;
    for(int i=1; i<=n+1; i++, cout<<'\n')
        for(int j=1; j<=n+1; cout<<matAd[i][j++]<<" ")
            ;
    cout<<endl<<endl;
}

void decodare() //codare
{

    int t[105];
    cin>>n;
    cout<<"Dati vectorul de tati: ";
    for(int i=1; i<=n; i++)
        cin>>t[i];
    int count=6;
    while(count--){

        int i, w;
        for(i=1; i<=n; i++)
        {   w=0;
            for(int j=1; j<=n; j++)
                if(t[j]==i) w=1;
            if(w==0) break;
        }
        cout<<t[i]<<" ";
        t[i]=i;

    }

}

int main(){

    int cmd;
    cout<<"1 - Decodare | 2 - Codare: ";
    cin>>cmd;
    cmd==1?codare():decodare();
    return 0;

}
