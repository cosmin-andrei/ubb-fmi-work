#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
#include <vector>
#define MAX 1000
using namespace std;

queue<int> Q; //coada
int Graph[MAX][MAX],n,d[100],p[100];

int Bellman(int start) {

	//initializare
	for (int i = 1; i <= n; i++)
	{
		d[i] = INT_MAX;
		p[i] = NULL;
	}

	d[start] = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (Graph[i][j])
				if (d[j] > d[i] + Graph[i][j])
				{
					d[j] = d[i] + Graph[i][j];
					p[j] = i;
				}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (Graph[i][j])
				if (d[j] > d[i]+Graph[i][j])
					return false;

	return true;

}

int main(int argc, char * argv[])
{
	//ifstream fin(argv[1]);
	ifstream fin("graf.txt");

	int start, m;

	fin>>n>>m>>start;
	cout << n << " " << m << " " << start;
	for (int i = 1; i <= m; i++) {
		int x, y, c;
		fin >> x >> y >> c;
		Graph[x][y] = c;
	}

	fin.close();

	bool ok = Bellman(start);

	ofstream fout("g.txt");

	if (ok == true) {
		for (int i = 1; i <= n; i++)
			if (i != start && d[i] != MAX)
				fout << "Drumul " << start << "->" << i << " este de cost " << d[i] << "\n";
	}
	else cout << "eroare";

	fout.close();
	return 0;
}
