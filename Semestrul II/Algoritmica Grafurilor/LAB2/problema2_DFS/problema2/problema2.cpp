#include <iostream>
#include <fstream>
using namespace std;

int n, m, mat[100][100], matTranz[100][100], viz[100]; // mat-Matricea de adiacenta

//algoritmul DFS
void DFS(int nod)
{
    viz[nod] = 1;
    for (int j = 1; j <= n; j++)
        if (mat[nod][j] == 1 && viz[j] != 1) DFS(j);
}

int main()
{
    ifstream fin("graf.txt");
    int n, m, x, y;
    fin >> n;
    fin >> m;

    while (fin >> x >> y)
    {
        mat[x][y] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int d = 1; d <= n; d++)
            viz[d] = 0;

        DFS(i);
        for (int j = 1; j <= n; j++)
        {
            // if (i == j) continue;
            if (viz[j]) matTranz[i][j + 1] = 1;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << endl;
        for (int j = 1; j <= n; j++)
            cout << matTranz[i][j] << " ";
    }

    return 0;
}
