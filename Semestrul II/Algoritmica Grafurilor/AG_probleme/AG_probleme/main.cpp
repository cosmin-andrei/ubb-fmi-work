#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
#include <cstring>
#include <string>

using namespace std;

ifstream fin("file_in.txt");
ofstream fout("file_out.txt");



void Ciclu_Eulerian() {
    printf("Ciclu eulerian\n");
}
/*
5 6
0 1
0 2
1 2
2 3
2 4
3 4
*/
/*

#define dim 100
int n, m, g[dim][dim], ciclu[dim];
int p = 0;
void Ciclu_Eulerian(int k) {
    for (int i = 0; i < n; i++)
        if (g[k][i]) {
            g[k][i] = g[i][k] = 0;
            Ciclu_Eulerian(i);
        }
    ciclu[p] = k;
    p++;
}
int main(){
    int x, y;

    fin >> n >> m;
    for(int i = 1; i <= m; i++){
        fin >> x >> y;
        g[x][y] = g[y][x] = 1;
    }

    Euler(0);
    cout << p;
    for(int i = 0; i < p; i++)
        fout << ciclu[i] << ' ';
}
*/










void Codare_Prufer() {
    printf("Codare prufer\n");
}
/*
7
-1 0 1 1 2 0 5
*/
/*

#define dim 100
int n, p[dim], radacina, i;
priority_queue<int> T;
void codare_prufer()
{
    queue<int> K;
    queue<int> scoase;

    while (!T.empty())
    {
        bool gasit = true;
        int nod = -T.top();
        scoase.push(nod);
        T.pop();
        for (i = 0; i < n; i++)
        {
            if (p[i] == nod && i != radacina)
            {
                gasit = false;
            }
        }
        if (gasit)
        {
            K.push(p[nod]);
            // punem nodurile inapoi in afara de nod
            while (!scoase.empty())
            {

                if (scoase.front() != nod)
                    T.push(-scoase.front());

                scoase.pop();
            }
            p[nod] = -1;
        }
    }

    // afisare
    fout << K.size() << endl;
    while (!K.empty())
    {
        fout << K.front() << ' ';
        K.pop();
    }
    fout << endl;
}
int main() {
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> p[i];
        if (p[i] == -1)
            radacina = i;
        else
        {
            T.push(-i);
        }
    }
    fout << "Codare Prufer:\n";
    codare_prufer();
}
*/










void Decodare_Prufer() {
    printf("Decodare Prufer\n");
}
/*
6
1 2 1 0 5 0
*/
/*

#define dim 100
int m, k, MAX = INT_MIN;
int frecventa[dim];
queue<int> Kk;
void decodare_prufer()
{
    int t[dim];
    int nrt = 0;
    memset(t, -1, sizeof(t));
    // cout << t[0] << t[1] << t[100] << endl;

    for (int i = 0; i < m; i++)
    {
        int x = Kk.front();
        Kk.pop();
        int y = 0, j = 0;

        j = 0;
        while (j <= MAX)
        {
            if (frecventa[j] == 0)
                break;
            j++;
        }
        if (j > MAX)
            MAX = j;

        Kk.push(j);
        frecventa[j]++;

        y = j;
        t[y] = x;
        frecventa[x]--;
    }
    int noduri = MAX + 1;

    fout << noduri << endl;
    for (int i = 0; i < noduri; i++)
    {
        fout << t[i] << ' ';
    }
}
int main()
{
    fin >> m;
    for (int i = 0; i < m; i++)
    {
        fin >> k;
        Kk.push(k);
        frecventa[k]++;
        if (MAX < k)
            MAX = k;
    }

    fout << "Decodare Prufer:\n";
    decodare_prufer();
}
*/










void Flux_Maxim__Ford_Fulkerson() {
    printf("Flux_Maxim__Ford_Fulkerson\n");
}
/*
5 6
0 1 5
0 3 5
0 2 10
1 4 11
2 3 2
3 4 8
*/
/*

#define dim 100
int n, m, g[dim][dim];
bool BFS(int s, int d, int parent[]) {
    queue <int> Q;
    bool visited[dim];
    memset(visited, 0, sizeof(visited));

    visited[s] = true;
    parent[s] = -1;

    Q.push(s);
    while (!Q.empty()) {
        int nod = Q.front();
        Q.pop();
        for (int i = 0; i < n; i++) {
            if (visited[i] == false && g[nod][i] > 0) {
                if (i == d) {
                    parent[i] = nod;
                    return true;
                }
                Q.push(i);
                parent[i] = nod;
                visited[i] = true;

            }
        }
    }
    // nu am gasit drum de la s la t
    return false;
}
void Flux_Maxim__Ford_Fulkerson(int s, int d) {

    int parent[dim];
    int max_flow = 0;

    while (BFS(s, d, parent)) {
        int path_flow = INT_MAX;
        for (int i = d; i != s; i = parent[i]) {
            int u = parent[i];
            path_flow = min(path_flow, g[u][i]);
        }

        for (int i = d; i != s; i = parent[i]) {
            int u = parent[i];
            g[u][i] -= path_flow;
            g[i][u] += path_flow;
        }

        max_flow += path_flow;
    }
    fout << "Fluxul maxim este: " << max_flow;
}

int main() {
    int x, y, capacitate;

    fin >> n >> m;
    for (int i = 1; i <= m; i++) {
        fin >> x;
        fin >> y;
        fin >> capacitate;
        g[x][y] = capacitate;
    }
    Flux_Maxim__Ford_Fulkerson(0, n - 1);
}
*/










void Codare_Huffman() {
    printf("Codare_Huffman\n");
}
/*
Loorrreem
*/
/*

string c;
struct varf
{
    int stang;
    int drept;
    int fr;
    char c;
    string cod;
}z[10005];
priority_queue<pair<pair<int, char>, int>, vector<pair<pair<int, char>, int> >, greater<pair<pair<int, char>, int> > > q3;
int n3, fr[300], k, frunze;
int main()
{
    ifstream inFile;
    inFile.open("file_in.txt");
    inFile >> c;
    n3 = c.size();
    for (int i = 0;i < n3;i++)
    {
        fr[c[i]]++;
    }
    for (int i = 0;i <= 256;i++)
    {
        if (fr[i] != 0)
        {
            k++;
            z[k].c = (char)i;
            z[k].fr = fr[i];
            q3.push({ {fr[i],z[k].c},k });
        }
    }
    fout << k << '\n';
    frunze = k;
    for (int i = 1;i < frunze;i++)
    {
        k++;
        int indice = q3.top().second;
        int frec = q3.top().first.first;
        z[k].c = z[indice].c;
        z[k].stang = indice;
        z[k].fr = frec;
        q3.pop();
        int indice1 = q3.top().second;
        int frec1 = q3.top().first.first;
        z[k].drept = indice1;
        z[k].fr += frec1;
        if (z[indice1].c < z[k].c)
        {
            if (frec == frec1) swap(z[k].stang, z[k].drept);
            z[k].c = z[indice1].c;
        }
        q3.pop();
        q3.push({ {z[k].fr,z[k].c},k });
    }
    for (int i = 0;i <= 256;i++)
    {
        if (fr[i] != 0)
        {
            fout << (char)i << " " << fr[i] << '\n';
        }
    }
    for (int i = k;i > frunze;i--)
    {
        for (int j = 0;j < z[i].cod.size();j++)
        {
            z[z[i].stang].cod.push_back(z[i].cod[j]);
            z[z[i].drept].cod.push_back(z[i].cod[j]);
        }
        z[z[i].stang].cod.push_back('0');
        z[z[i].drept].cod.push_back('1');
    }
    for (int i = 0;i < c.size();i++)
    {
        for (int j = 1;j <= frunze;j++)
        {
            if (z[j].c == c[i])
            {
                fout << z[j].cod;
                break;
            }
        }
    }
    return 0;
}
*/










void Decodare_Huffman() {
    printf("Decodare Huffman\n");
}
/*
5
L 1
e 2
m 1
o 2
e 3
00010101111110101001
*/
/*

priority_queue<pair<pair<int, char>, int>, vector<pair<pair<int, char>, int> >, greater<pair<pair<int, char>, int> > >q4;
string c1, cod;
struct carc
{
    char c;
    int fr;
}v[300];
struct varf
{
    int stang;
    int drept;
    int fr;
    char c;
    string cod;
}z1[10005];

int n4, frunze1, k1;
bool compare(carc a, carc b)
{
    return a.fr < b.fr || a.fr == b.fr && a.c < b.c;
}

int main()
{
    fin >> n4;
    //fin.get();
    for (int i = 1;i <= n4 + 1;i++)
    {
        if (i <= n4) {
            char ch;
            int a;
            fin >> v[i].c;
            fin >> v[i].fr;
        }
        else if (i == n4 + 1) {
            fin >> c1;
        }
       
    }

    sort(v + 1, v + n4 + 1, compare);
    for (int i = 1;i <= n4;i++)
    {
        z1[i].c = v[i].c;
        z1[i].fr = v[i].fr;
        q4.push({ {z1[i].fr,z1[i].c},i });
    }
    frunze1 = n4;
    k1 = n4;
    for (int i = 1;i < frunze1;i++)
    {
        k1++;
        int indice = q4.top().second;
        int frec = q4.top().first.first;
        z1[k1].c = z1[indice].c;
        z1[k1].stang = indice;
        z1[k1].fr = frec;
        q4.pop();
        int indice1 = q4.top().second;
        int frec1 = q4.top().first.first;
        z1[k1].drept = indice1;
        z1[k1].fr += frec1;
        if (z1[indice1].c < z1[k1].c)
        {
            if (frec == frec1) swap(z1[k1].stang, z1[k1].drept);
            z1[k1].c = z1[indice1].c;
        }
        q4.pop();
        q4.push({ {z1[k1].fr,z1[k1].c},k1 });
    }
    for (int i = k1;i > frunze1;i--)
    {
        for (int j = 0;j < z1[i].cod.size();j++)
        {
            z1[z1[i].stang].cod.push_back(z1[i].cod[j]);
            z1[z1[i].drept].cod.push_back(z1[i].cod[j]);
        }
        z1[z1[i].stang].cod.push_back('0');
        z1[z1[i].drept].cod.push_back('1');
    }
    
   
    //getline(cin, c1);

    for (int i = 0;i < c1.size();i++)
    {
        cod.push_back(c1[i]);
        for (int j = 1;j <= frunze1;j++)
        {
            if (cod == z1[j].cod)
            {
                fout << z1[j].c;
                cod.clear();
                break;
            }
        }
    }
    return 0;
}
*/







void Arbore_min_Kruskal() {
    printf("Arbore_min_Kruskal\n");
}
/*
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
*/
/*

struct muchie { int x, y, c; } u[4951], sol[101];
void Kruskal()
{
    int n, m, L[101];
    fin >> n >> m;
    int i, j;
    for (i = 1; i <= m; i++)
        fin >> u[i].x >> u[i].y >> u[i].c;

    for (i = 1; i < m; i++)
        for (j = i + 1; j < m; j++)
            if (u[i].c > u[j].c) {
                muchie aux = u[i]; u[i] = u[j]; u[j] = aux;
            }

    for (i = 1; i <= n; i++) L[i] = i;
    int cost = 0, k = 0;
    i = 1;

    while (k < n - 1) {
        int arbx = L[u[i].x], arby = L[u[i].y];
        if (arbx != arby) {
            sol[++k] = u[i]; cost += u[i].c;
            for (j = 1; j <= n; j++)
                if (L[j] == arby) L[j] = arbx;
        }
        i++;
    }
    fout << cost << '\n';
    for (i = 1; i <= k; i++) 
        fout << sol[i].x << " " << sol[i].y << '\n';
}
int main() {
    Kruskal();
    return 0;
}
*/



void Arbore_min_Prim() {
    printf("Arbore min Prim\n");
}
/*
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
*/
/*

const int inf = 0x3FFFFFFF;
int a[101][101], viz[101], c[101], t[101];
void Prim()
{
    int n, m;
    fin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                a[i][j] = inf;
    for (int p, q, cost, i = 1; i <= m; i++)
    {
        fin >> p >> q >> cost;
        a[p][q] = cost;
        a[q][p] = cost;
    }
    for (int j = 1; j <= n; j++)
    {
        c[j] = a[1][j];
        if (j != 1) t[j] = 1;
    }

    viz[1] = 1; c[0] = inf;
    int cost = 0;
    for (int k = 2; k <= n; k++)
    {
        int min_c = 0;
        for (int i = 1; i <= n; i++)
            if (!viz[i] and c[i] < c[min_c])
                min_c = i;
        viz[min_c] = 1;
        for (int i = 1; i <= n; i++)
            if (!viz[i] and c[i] > a[min_c][i])
            {
                c[i] = a[min_c][i];
                t[i] = min_c;
            }
    }
    for (int i = 1; i <= n; i++)
        cost += c[i];
    fout << cost << '\n';
    for (int i = 1; i <= n; i++)
        fout << t[i] << ' ';
}
int main() {
    Prim();
    return 0;
}
*/










void Flux_Maxim__Edmonds_Karp() {
    printf("Edmonds-Karp\n");
}
/*
5 6
0 1 5
0 3 5
0 2 10
1 4 11
2 3 2
3 4 8
*/
/*

int graph[100][100];
#define dim 100
bool bfs(int rGraph[dim][dim], int s, int t, int parent[])
{
    bool visited[dim];
    memset(visited, 0, sizeof(visited));
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < dim; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
int edmond_karp( int s, int t)
{
    int u, v;
    int rGraph[dim][dim];

    for (u = 0; u < dim; u++)
        for (v = 0; v < dim; v++)
            rGraph[u][v] = graph[u][v];

    int parent[dim];  
    int max_flow = 0;  
    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}
int main(){
    int n, m;
    int x, y, capacitate;

    fin >> n >> m;
    for (int i = 1; i <= m; i++) {
        fin >> x;
        fin >> y;
        fin >> capacitate;
        graph[x][y] = capacitate;
    }

    fout << "Fluxul maxim este: " << edmond_karp(0, n-1);
    return 0;
}
*/








int main() {
    Arbore_min_Kruskal();
    Arbore_min_Prim();

    Flux_Maxim__Ford_Fulkerson();
    Flux_Maxim__Edmonds_Karp();
    //Flux_Maxim__Pompare_Preflux(); ->nu am
    //Flux_Maxim__Pompare_Topologica(); ->nu am
    Ciclu_Eulerian();

    Codare_Prufer();
    Decodare_Prufer();

    Codare_Huffman();
    Decodare_Huffman();
}
