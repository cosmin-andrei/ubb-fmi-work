
///----------- KRUSKAL -------------

#include <iostream>
using namespace std;

struct muchie{int x,y,c;} u[4951], sol[101];

void Kruskal()
{   int n, m, L[101];
    cin>>n>>m;
    int i, j;
    for(i=1; i<=m; i++)
        cin>>u[i].x>>u[i].y>>u[i].c;

    for(i=1; i<m; i++)
        for(j=i+1; j<m; j++)
            if(u[i].c>u[j].c){
                muchie aux=u[i]; u[i]=u[j]; u[j]=aux;
            }

    for(i=1; i<=n; i++) L[i]=i;
    int cost=0, k=0;
    i=1;

    while(k<n-1){
        int arbx=L[u[i].x], arby=L[u[i].y];
        if(arbx!=arby){
            sol[++k]=u[i]; cost+=u[i].c;
            for(j=1; j<=n; j++)
                if(L[j]==arby) L[j]=arbx;
        }
        i++;
    }
    cout<<cost<<'\n';
    for(i=1; i<=k; i++) cout<<sol[i].x<<" "<<sol[i].y<<'\n';
}
 ///--------- PRIM -----------

const int inf = 0x3FFFFFFF;
int a[101][101], viz[101], c[101], t[101];

void Prim()
{
    int n, m;
    cin >> n >>m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                a[i][j] = inf;
    for(int p,q,cost,i=1;i<=m;i++)
    {   cin>>p>>q>>cost;
        a[p][q]=cost;
        a[q][p]=cost;
    }
    for (int j = 1; j <= n; j++)
    {
        c[j] = a[1][j];
        if (j != 1) t[j] = 1;
    }

    viz[1] = 1; c[0] = inf;
    int cost=0;
    for (int k = 2; k <= n; k++)
    {
        int min_c = 0;
        for (int i = 1; i <= n; i++)
            if (!viz[i] and c[i] < c[min_c])
                min_c = i;
        viz[min_c] = 1;
        for (int i = 1; i <= n; i++)
            if (!viz[i] and c[i] >a[min_c][i])
            {
                c[i] = a[min_c][i];
                t[i] = min_c;
            }
    }
    for(int i=1;i<=n;i++)
        cost+=c[i];
    cout<<cost<<'\n';
    for(int i=1;i<=n;i++)
        cout<<t[i]<<' ';
}

int main(){

    int cmd;
    cout<<"1 - Kruskal | 2 - Prim: ";
    cin>>cmd;
    cmd==1?Kruskal():Prim();

    return 0;

}

/*

^^ IN ^^
7 11
1 2 2
1 7 4
2 3 3
2 5 2
2 6 3
2 7 3
3 4 1
3 5 2
4 5 1
5 6 3
6 7 5

^^ KRUSKAL OUT ^^
12
3 4
4 5
1 2
2 5
2 6
2 7

^^ PRIM OUT ^^
12
0 1 4 5 2 2 2

*/
