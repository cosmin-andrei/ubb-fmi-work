#include <fstream>
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;
ifstream f("graf.txt");
vector <int> lVecini[105];
queue <int> Q;
int lant[105], parinte[105], rezultat[105];
int main()
{
    int n, x, y, p, v;
    f>>n;
    while(f>>x>>y)
        lVecini[x].push_back(y);
    cout<<"Introduceti nodul initial: ";
    cin>>p;
    cout<<"Introduceti nodul final: ";
    cin>>v;

    for(int i=1; i<=n; i++)
        if(i!=p) lant[i]=LONG_MAX;

    Q.push(p);
    while(!Q.empty())
    {   x=Q.front();
        //cout<<x<<" ";
        Q.pop();
        for(unsigned int i=0; i<lVecini[x].size(); i++)
            if(lant[lVecini[x][i]]==LONG_MAX)
            {   parinte[lVecini[x][i]]=x;
                lant[lVecini[x][i]]=lant[x]+1;
                Q.push(lVecini[x][i]);
            }
    }
    int k=lant[v], k2=lant[v];
    rezultat[k]=v;
    while(k)
    {   rezultat[k-1]=parinte[rezultat[k]];
        k--;
    }

    cout<<'\n'<<"Drumul minim: ";
    for(int i=1; i<=k2; i++)
        cout<<rezultat[i]<<" ";
    return 0;
}
