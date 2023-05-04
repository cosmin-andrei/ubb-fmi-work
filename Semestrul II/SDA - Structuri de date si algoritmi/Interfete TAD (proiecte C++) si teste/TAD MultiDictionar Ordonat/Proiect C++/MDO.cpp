#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;

void MDO::redimensionare()
{/* Complexitate theta(n) */
	int new_capacity = 2 * capacitate;
	Nod* copie_element = new Nod[new_capacity];
	int* copie_stang = new int[new_capacity];
	int* copie_drept = new int[new_capacity];
	int* copie_urmator = new int[new_capacity];

	for (int i = 0; i < capacitate; i++)
	{
		copie_element[i] = element[i];
		copie_stang[i] = stang[i];
		copie_drept[i] = drept[i];
		copie_urmator[i] = urmator[i];
	}

	for (int i = capacitate; i < new_capacity; i++)
		copie_urmator[i] = i + 1;

	delete[]element;
	delete[]stang;
	delete[]drept;
	delete[]urmator;

	capacitate = new_capacity;
	element = copie_element;
	stang = copie_stang;
	drept = copie_drept;
	urmator = copie_urmator;
}

MDO::MDO(Relatie r) {
	/* Complexitate theta(n) */
	rel = r;
	capacitate = 5;
	lungime = 0;
	primLiber = 0;

	radacina = NIL;
	element = new Nod[capacitate];
	stang = new int[capacitate];
	drept = new int[capacitate];
	urmator = new int[capacitate];

	for (int i = 0; i < capacitate; i++)
	{
		element[i].c = NIL;
		stang[i] = NIL;
		drept[i] = NIL;
		urmator[i] = i + 1;
	}
}


void MDO::adauga(TCheie c, TValoare v)
{/* Complexitate O(h) */

	if (primLiber == capacitate)/* S-a ajuns la capacitate maxima, redimensionare */
		redimensionare();

	lungime++;

	if (vid())/* multidictionarul este vid */
	{/* Initializez radacina */
		radacina = primLiber;
		element[radacina].c = c;
		element[radacina].valori.push_back(v);
		stang[radacina] = NIL;
		drept[radacina] = NIL;
		primLiber = urmator[primLiber];
		return;
	}

	/* Parcurg arborele si caut locul in care trebuie adaugat elementul */
	int curent = radacina;
	int parent = NIL;
	while (curent != NIL && element[curent].c != c)
	{
		parent = curent;
		if (rel(c, element[curent].c))
			curent = stang[curent];
		else
			curent = drept[curent];
	}

	if (curent != NIL && element[curent].c == c)
	{/* Cheia se afla deja */
		element[curent].valori.push_back(v);
		return;
	}
	else
	{/* Se adauga o cheie noua*/
		element[primLiber].c = c;
		element[primLiber].valori.push_back(v);
		stang[primLiber] = NIL;
		drept[primLiber] = NIL;

		/* Adaug in functie de relatie cu parintele pentru a pastra multidictionarul ordonat */
		if (rel(c, element[parent].c))
			stang[parent] = primLiber;
		else
			drept[parent] = primLiber;

		primLiber = urmator[primLiber];
		return;
	}
}

vector<TValoare> MDO::cauta(TCheie c) const
{/* Complexitate O(h) */
	if (vid())
		return vector<TValoare>();

	int curent = radacina;
	while (curent != NIL && element[curent].c != c)
	{
		if (rel(c, element[curent].c))
			curent = stang[curent];
		else
			curent = drept[curent];
	}

	if (curent != NIL && element[curent].c == c)
		return element[curent].valori;
	else
		return vector<TValoare>();
}

int MDO::maxim(int radacina)
{/* Functia determina nodul maxim dintr-un arbore */
	int nod_curent = radacina;
	int maxim = radacina;
	while (nod_curent != NIL)
	{
		maxim = nod_curent;
		nod_curent = drept[nod_curent];
	}
	return maxim;
}

int MDO::removeElement(int radacina, TElem e, bool& removed)
{/* Functie recursiva pentru eliminarea unui element(cheie,valoare)

	T(h) = k + T(h-1), unde k este numarul de valori ale unei chei c => Complexitate O(h), unde h este inaltimea arborelui */
	if (vid())/* este vid */
		return radacina;

	bool found = false;/* pp ca nu gasesc elementul*/

	if (e.first == element[radacina].c)/* Am gasit cheia */
	{/* Caut printre valorile cheii */
		for (const auto& valoare : element[radacina].valori)
			if (valoare == e.second)
			{
				found = true;
				break;
			}

		/* Am gasit elementul cautat, elimin*/
		if (found == true)
		{
			element[radacina].valori.erase(remove(element[radacina].valori.begin(), element[radacina].valori.end(), e.second));
			removed = true;
		}

		if (element[radacina].valori.empty())
		{/* Cazul in care si cheia trebuie eliminata */
			if (stang[radacina] == NIL)
			{/* Nu are descendent stang */
				int descendentDrept = drept[radacina];
				element[radacina].c = NIL;
				drept[radacina] = NIL;

				urmator[radacina] = primLiber;
				primLiber = radacina;
				return descendentDrept;
			}
			else
				if (drept[radacina] == NIL)
				{/* Nu are descendent drept */
					int descendentStang = stang[radacina];
					element[radacina].c = NIL;
					stang[radacina] = NIL;

					urmator[radacina] = primLiber;
					primLiber = radacina;
					return descendentStang;
				}
				else
				{/* Are descendent stang si drept */
					int maximStang = maxim(stang[radacina]);/* maximul din subarborele stang */
					/* Inlocuiesc radacina cu aceasta valoare */
					element[radacina].c = element[maximStang].c;
					drept[radacina] = drept[maximStang];
					stang[radacina] = stang[maximStang];
					/* Elimin acest element maxim gasit */
					TElem e2 = pair<TCheie, TValoare>(element[maximStang].c, element[maximStang].valori[0]);
					stang[radacina] = removeElement(stang[radacina], e2, removed);
				}
		}
	}
	else
		/* Daca inca nu am gasit cheia, caut in continuare */
		if (rel(e.first, element[radacina].c) && stang[radacina] != NIL)
			stang[radacina] = removeElement(stang[radacina], e, removed);
		else
			if (rel(element[radacina].c, e.first) && drept[radacina] != NIL)
				drept[radacina] = removeElement(drept[radacina], e, removed);

	return radacina;
}

bool MDO::sterge(TCheie c, TValoare v)
{/* Complexitate O(h) */

	bool removed = false;/* pp ca stergerea nu este cu succes */
	TElem element = pair<TCheie, TValoare>{ c,v };
	radacina = removeElement(radacina, element, removed);
	if (removed)
		lungime--;
	return removed;
}

int MDO::dim() const
{/* COMPLEXITATE theta(1) */
	return lungime;
}

bool MDO::vid() const
{/* COMPLEXITATE theta(1) */

	if (radacina == NIL)
		return true;

	return false;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

vector<TCheie> MDO::multimeaCheilor() const
{
	IteratorMDO it = iterator();
	it.prim();
	vector<TCheie> cheiMDO;

	while (it.valid())
	{
		cheiMDO.push_back(element[it.curent].c);
		it.urmator();
	}

	return cheiMDO;
}

MDO::~MDO()
{
	/* COMPLEXITATE theta(1) */
	delete[]element;
	delete[]stang;
	delete[]drept;
	delete[]urmator;
}