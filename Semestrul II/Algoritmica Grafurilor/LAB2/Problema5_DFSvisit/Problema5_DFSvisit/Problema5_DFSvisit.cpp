#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> G[100];
int v[100]; //vector de vizitare

void DFS_VISIT(int n)
{
    v[n] = 1;
    cout << n << " "; //nod curent
    for (int i=0; i<G[n].size(); i++)
    {
        int nod = G[n][i];
        if (!v[nod])
        {
            cout << nod << " "; //vecin nevizitat
            DFS_VISIT(nod);
        }
    }
}

void DFS(int n)
{
    for (int i = 1; i <= n; i++)
        if (!v[i]) DFS_VISIT(i); //apelam DFS_VISIT pe vârfurile nevizitate
}

int main()
{

    ifstream fin("graf.txt");
    int n, x, y;
    fin >> n;

    while (fin >> x >> y)
    {
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DFS(n);

    return 0;
}