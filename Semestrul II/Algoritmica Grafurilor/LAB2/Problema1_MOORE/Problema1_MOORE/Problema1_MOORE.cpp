#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

vector<int> G[100]; //vector de vectori

int l[100], p[100], r[100]; // l-lant, p-parinte, r-rezultat
queue<int> Q; //definire coada

int main()
{

	ifstream f("graf.txt");
	int n, x, y, start, final;
	f >> n;
	while (f>>x>>y)
	{
		G[x].push_back(y);
		G[y].push_back(x);
	}
	f.close();

	cout << "Introduceti nodul initial: ";
	cin >> start;

	cout << "Introduceti nodul final: ";
	cin >> final;

	if (start < 0 || start > n || final < 0 || final > n) {
		cout << "Noduri invalide!";
		return 1;
	}

	for (int i = 1; i <= n; i++)
		if (i != start) 
			l[i] = INT_MAX; // initializam toate nodurile cu INT_MAX

	Q.push(start); // pune start la sfarsitul cozii

	//algoritmul de cautare a drumului minim - Alg lui Moore (BFS)
	while (!Q.empty())
	{
		int x = Q.front(); // returneaza elementul de la inceputul cozii
		Q.pop();
		for (int i = 0; i < G[x].size(); i++)
			if (l[G[x][i]] == INT_MAX)
			{
				p[G[x][i]] = x;
				l[G[x][i]] = l[x] + 1;
				Q.push(G[x][i]);
			}
	}

	int k = l[final];
	r[k] = final;
	
	//distant minima
	while (k)
	{
		r[k - 1] = p[r[k]];
		k--;
	}

	if (r[1]==0) {
		cout << "Nu exista drum intre " << start << " si " << final;
		return 1;
	}

	cout << '\n' << "Drumul minim: ";
	for (int i = 0; i <= l[final]; i++)
		cout << r[i] << " ";

	return 0;
}
