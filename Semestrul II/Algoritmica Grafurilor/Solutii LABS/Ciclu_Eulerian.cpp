#include <iostream>

using namespace std;
int n, m, p, a[205][205], L[50000];

void Euler(int k)
{   for(int i=1; i<=n; i++)
		if(a[k][i]){
            a[k][i]=a[i][k]=0;
			Euler(i);
		}
	L[++p]=k;
}
int main()
{   int i, j;
    cin>>n>>m;
    for(int K=1; K<=m; K++){
        cin>>i>>j;
        a[i][j]=a[j][i]=1;
    }
    Euler(1);
	cout<<p<<"\n";
	for(int i=1;i<=p;i++) cout<<L[i]<<" ";
	return 0;
}

/*
^^ IN ^^
6 9
1 2
1 3
2 3
2 4
2 5
3 5
3 6
4 5
5 6

^^ OUT ^^
10
1 2 4 5 3 6 5 2 3 1
*/
