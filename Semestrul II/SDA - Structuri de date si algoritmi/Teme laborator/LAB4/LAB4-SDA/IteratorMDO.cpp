#include "IteratorMDO.h"
#include "MDO.h"

//BC=AC=WC=Theta(1)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	if (d.dim() == 0) {
		curent = nullptr;
		curentPozitie = INT_MIN;
	}
	else
	{
		curent = dict.elem[dict.prim];
		curentPozitie = dict.prim;
	}
}

//BC=AC=WC=Theta(1)
void IteratorMDO::prim() {
	if (dict.dim() == 0) {
		curent = nullptr;
		curentPozitie = INT_MIN;
	}
	else
	{
		curent = dict.elem[dict.prim];
		curentPozitie = dict.prim;
	}
}

//BC=AC=WC=Theta(1)
void IteratorMDO::urmator() {
	if (valid())
	{
		if (curent->urmator != nullptr) {
			curent = curent->urmator;
		}
		else {
			curentPozitie = dict.urm[curentPozitie];
			if (curentPozitie == INT_MIN)
				return;
			curent = dict.elem[curentPozitie];
		}
	}
	else
		throw exception();
}

//BC=AC=WC=Theta(1)
bool IteratorMDO::valid() const {
	return (curent != NULL && curentPozitie != INT_MIN);
}

//BC=AC=WC=Theta(1)
TElem IteratorMDO::element() const {
	if (valid())
		return pair <TCheie, TValoare>(curent->element.first, curent->element.second);
	else
		throw exception();
}

//BC=AC=WC=Theta(1)
TCheie IteratorMDO::cheie() const {
	return curent->element.first;
}

//BC=AC=WC=Theta(n)
vector<TValoare> IteratorMDO::valori() const {
	vector<TValoare> rezultat;

	MDO::Nod* nodCurent = curent;
	while (nodCurent != nullptr) {
		rezultat.push_back(nodCurent->element.second);
		nodCurent = nodCurent->urmator;
	}

	return rezultat;
}