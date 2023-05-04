#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#define inf 1000000000
using namespace std;
ifstream f("in.txt");
int a[105][105], n, m, d[105], p[105];

void Bellman(int nod){
    cout<<"!!Algoritmul lui Bellman!!\n\n";

    for(int i=1; i<=n; i++)
        d[i]=inf, p[i]=nod;
    d[nod]=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(a[i][j])
                if(d[j]>d[i]+a[i][j])
                    d[j]=d[i]+a[i][j], p[j]=i;
    for(int i=1; i<=n; i++)
        if(i!=nod)
            cout<<"Drumul de la "<<nod<<" la "<<i<<" este de cost "<<d[i]<<'\n';
    cout<<endl;
    for(int i=1; i<=n; i++)
        if(i!=nod){
            cout<<"Drumul invers de la "<<nod<<" la "<<i<<" este: "<<i<<" ";
            int dc=p[i];
            while(dc!=nod)
            {
                cout<<dc<<" ";
                dc=p[dc];
            }
            cout<<dc;
            cout<<endl;
        }
}

void Dijkstra(int nod){
    cout<<"!!Algoritmul lui Dijkstra!!\n\n";

    priority_queue <int> Q;
    vector <int> s;
    for(int i=1; i<=n; i++){
        Q.push(-i);
        d[i]=inf;
        p[i]=nod;
    }
    d[nod]=0;
    while(!Q.empty()){
        int u = -Q.top();
        Q.pop();
        s.push_back(u);
        for(int j=1; j<=n; j++)
            if(a[u][j])
                if(d[j]>d[u]+a[u][j])
                    d[j]=d[u]+a[u][j], p[j]=u;
    }
    for(int i=1; i<=n; i++)
        if(i!=nod)
            cout<<"Drumul de la "<<nod<<" la "<<i<<" este de cost "<<d[i]<<'\n';
    cout<<endl;
    for(int i=1; i<=n; i++)
        if(i!=nod){
            cout<<"Drumul invers de la "<<nod<<" la "<<i<<" este: "<<i<<" ";
            int dc=p[i];
            while(dc!=nod)
            {
                cout<<dc<<" ";
                dc=p[dc];
            }
            cout<<dc;
            cout<<endl;
        }

}

int main()
{
    f>>n>>m;
    int nod; f>>nod;
    for(int j=1; j<=m; j++){
        int x, y, c;
        f>>x>>y>>c;
        a[x][y]=c;
    }
    Bellman(nod);
    Dijkstra(nod);
    return 0;
}
