#include<fstream>
#include <cstring>
#include<string>
#include<deque>
#include<vector>
using namespace std;
ifstream f("Labirint.in");
ofstream g("out.txt");

int a[1000][1000], n, m;
int xstart, ystart, xfinish, yfinish;
char str[1000];
deque<int>q;
deque<int>v[1001];

void bordare(int n, int m) {
	for (int i = 0; i <= n + 1; i++) {
		a[i][0] = a[i][m + 1] = -1;
	}
	for (int i = 0; i <= m + 1; i++) {
		a[0][i] = a[n+1][i] = -1;
	}
}

void seted() {
	int pz = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 0) {
				a[i][j] = pz;
				pz++;
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++) {
			if (a[i][j] != -1) {
				if (a[i - 1][j] != -1) {
					v[a[i - 1][j]].push_back(a[i][j]);
					v[a[i][j]].push_back(a[i - 1][j]);
				}
				if (a[i][j - 1] != -1) {
					v[a[i][j - 1]].push_back(a[i][j]);
					v[a[i][j]].push_back(a[i][j - 1]);
				}
			}
		}
	}
}

bool visited[10001];
int val[10001];

void bfs()
{
	q.push_back(a[xstart][ystart]);
	visited[a[xstart][ystart]] = 1;
	while (!q.empty()) {
		int nod = q.front();
		q.pop_front();
		for (int i = 0; i < v[nod].size(); i++) {
			if (visited[v[nod][i]] == 0) {
				visited[v[nod][i]] = 1;
				val[v[nod][i]] = val[nod] + 1;
				q.push_back(v[nod][i]);
			}
		}
	}
}

void drum() {
	int i = xfinish;
	int j = yfinish;
	while (i != xstart || j != ystart) {
		g << i << " " << j << "\n";
		if (a[i - 1][j] != -1 && val[a[i - 1][j]] + 1 == val[a[i][j]]) {
			i--;
		}
		else if (a[i + 1][j] != -1 && val[a[i + 1][j]] + 1 == val[a[i][j]]) {
			i++;
		}
		else if (a[i][j - 1] != -1 && val[a[i][j - 1]] + 1 == val[a[i][j]]) {
			j--;
		}
		else if (a[i][j + 1] != -1 && val[a[i][j + 1]] + 1 == val[a[i][j]]) {
			j++;
		}
	}
	g << i << " " << j << "\n";
}

int main()
{
	f.getline(str, 1000);
	m = strlen(str);
	n = 1;
	while (!f.eof())
	{
		for (int i = 0; i < m; i++) {
			if (str[i] == 'S')
			{
				xstart = n;
				ystart = i+1;
			}
			else if (str[i] == 'F')
			{
				xfinish = n;
				yfinish = i+1;
			}
			else if (str[i] == '1')
			{
				a[n][i+1] = -1;
			}
			else {
				a[n][i+1] = 0;
			}
		}
		n++;
		f.getline(str, 1000);
	}
	for (int i = 0; i < m; i++) {
		if (str[i] == 'S')
		{
			xstart = n;
			ystart = i + 1;
		}
		else if (str[i] == 'F')
		{
			xfinish = n;
			yfinish = i + 1;
		}
		else if (str[i] == '1')
		{
			a[n][i + 1] = -1;
		}
		else {
			a[n][i + 1] = 0;
		}
	}
	n++;
	bordare(n, m);
	seted();
	bfs();
	drum();
	return 0;
}
