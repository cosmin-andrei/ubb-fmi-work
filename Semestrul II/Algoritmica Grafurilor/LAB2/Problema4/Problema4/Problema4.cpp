#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

vector<int> G[100]; // vectorul de liste de adiacenta pt fiecare nod

int l[100], p[100], r[100]; // l-lant, p-parinte, r-rezultat
queue<int> Q; //coada

void bfs(int start, int n)
{
    //initializem toate nodurile fara start 
    for (int i = 1; i <= n; i++)
        if (i != start)
            l[i] = INT_MAX;

    Q.push(start);
    
    //BFS/ alg moore
    while (!Q.empty())
    {
        int x = Q.front();
        cout << "nod descoperit: " << x << ", distanta fata de nodul sursa: " << l[x] << endl;
        Q.pop();
        for (int i = 0; i < G[x].size(); i++)
            if (l[G[x][i]] == INT_MAX)
            {
                p[G[x][i]] = x;
                l[G[x][i]] = l[x] + 1;
                Q.push(G[x][i]);
            }
    }
}

int main()
{

    ifstream f("graf.txt");
    int n, x, y, start;
    f >> n;
    while (f >> x >> y)
    {
        G[x].push_back(y);
        G[y].push_back(x);
    }
    f.close();

    cout << "introduceti nodul initial: ";
    cin >> start;

    if (start < 0 || start > n) {
        cout << "Noduri invalide!";
        return 1;
    }

    bfs(start, n);

    return 0;
}