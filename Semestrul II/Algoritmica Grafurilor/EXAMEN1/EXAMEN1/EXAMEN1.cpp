/*
citim dintr un fisier un graf

lista adiacenta
cate varfuri izolate are graful respectiv
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("graf.txt");

int mat[105][105], l[105][104];

int main()
{
	int n,i,j;
	fin >> n;

	while (fin >> i >> j)
	{
		int k = 1;
		while (l[i][k] != 0)
			k++;
		l[i][k] = j;

		k = 1;
		while (l[j][k] != 0)
			k++;

		l[j][k] = i;
	}

	//afisez lista de adiacenta
	for (int i = 1; i <= n; i++)
	{
		if (l[i][1] == 0)
			cout << i << ": nod izolat";
		else{
		cout << i << ": ";
		for (int j = 1; j < n; j++)
			if (l[i][j] != 0)
				cout << l[i][j] << " ";
		}
		cout << endl;
	}

	//calculez numarul de noduri izolate
	int k = 0;
	for (int i = 1; i <= n; i++)
		if (l[i][1] == 0)k++;

	cout << "Nr noduri izolate: " << k;
}