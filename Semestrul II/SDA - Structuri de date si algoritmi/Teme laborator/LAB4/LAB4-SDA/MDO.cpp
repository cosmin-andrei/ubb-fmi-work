#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

// BC=AC=WC=Theta(1)
/*
* initializez elementele clasei și creez un MDO gol cu capacitate de 50
*/
MDO::MDO(Relatie r) {
    relatie = r;
    prim = -1;
    ultim = -1;
    capacitate = 50;
    urm = new int[capacitate];
    prec = new int[capacitate];
    elem = new Nod * [capacitate];
    for (int i = 0; i < capacitate; i++) {
        urm[i] = i + 1;
        prec[i] = -1; // Precedentul element din lista de la indexul i este -1 - nu există
        Nod* nod = new Nod; // Se creează un nou nod pentru elementul din lista de la indexul i
        nod->element.first = INT_MIN; // Inițializează cheia nodului cu valoarea minimă a unui întreg
        nod ->element.second = INT_MIN; // Inițializează valoarea nodului cu valoarea minimă a unui întreg
        elem[i] = nod; // Nodul de la indexul i este setat cu nodul nou creat
    }
}

//BC=Theta(1)
//WC=AC=Theta(n)
void MDO::adauga(TCheie c, TValoare v) {

    if (capacitate == dimensiune || c >= capacitate)
        redimensionare(); // redimensionează capacitatea MDO-ului daca este necesar

    else if (prim == -1) {
        // daca MDOul este gol, initializam
        prim = c;
        ultim = c;
        dimensiune = 1;
        elem[c]->element.first = c;
        elem[c]->element.second = v;
        elem[c]->urmator = nullptr; // nu exista un element următor
        elem[c]->precedent = nullptr; // nu exista un element precedent
        urm[c] = INT_MIN;
        prec[c] = -1;
    }

    // Cazul în care elementul trebuie adăugat la începutul MDO-ului
    else if (!relatie(prim, c) && c < capacitate) {
        urm[c] = prim;
        prec[c] = -1;
        prec[prim] = c;
        elem[c]->element.first = c;
        elem[c]->element.second = v;
        elem[c]->urmator = nullptr;
        elem[c]->precedent = nullptr;
        prim = c;
        dimensiune += 1;
    }

    // Cazul general în care elementul trebuie adăugat în interiorul MDO-ului
    else {

        // Elementul nu există în MDO, adăugăm un nou nod pentru el
        if (elem[c]->element.first == INT_MIN) {
            elem[c]->element.first = c;
            elem[c]->element.second = v;
            elem[c]->urmator = nullptr;
            elem[c]->precedent = nullptr;

            if (relatie(ultim, c)) {
                urm[ultim] = c;
                urm[c] = INT_MIN;
                prec[c] = ultim;
                ultim = c;
            }
            else {
                int elemcurent = prim;
                // Găsim poziția corectă pentru elementul c în lista ordonată
                while (relatie(elemcurent, c) && elemcurent != ultim)
                    elemcurent = urm[elemcurent];
                urm[c] = elemcurent;
                urm[prec[elemcurent]] = c;
                prec[c] = prec[elemcurent];
                prec[elemcurent] = c;
            }

            dimensiune += 1;
        }
        else {
            // Elementul există deja în MDO, adăugăm o nouă valoare pentru el
            Nod* NodNou = new Nod();
            Nod* curent = elem[c];
            NodNou->element.first = c;
            NodNou->element.second = v;
            NodNou->urmator = nullptr;
            while (curent->urmator != nullptr)
                curent = curent->urmator;
            NodNou->precedent = curent;
            curent->urmator = NodNou;
            dimensiune += 1;
        }
    }
}

// BC=WC=AC=Theta(n)
vector<TValoare> MDO::cauta(TCheie c) const {

    vector<TValoare> rezultat;

    // Verifică dacă cheia este validă sau elementul nu există în MDO
    if (c < 0 || c >= capacitate || elem[c]->element.first == INT_MIN)
        return rezultat;

    Nod* curent = elem[c];

    // Parcurge lista de noduri corespunzătoare cheii c și adaugă valorile în vectorul rezultat
    while (curent != nullptr) {
        rezultat.push_back(curent->element.second);
        curent = curent->urmator;
        if (curent == nullptr)
            break;
    }

    return rezultat;
}

//BC=WC=AC=Theta(n)
/*
* elimină o pereche cheie-valoare din MDO
* Parcuge lista de noduri corespunzătoare cheii c și verif dacă valorile se potrivesc
* Dacă găsește o potrivire, elimină nodul corespunzător
*/
bool MDO::sterge(TCheie c, TValoare v) {

    if (elem[c]->element.first == INT_MIN)
        return false;

    Nod* curent = elem[c];
    // Parcurge lista de noduri corespunzătoare cheii c
    while (curent != nullptr) {
        if (curent->element.first == c && curent->element.second == v) {

            // Nodul este primul din lista
            if (curent->precedent == nullptr) {
                curent->element.first = INT_MIN;
                curent->element.second = INT_MIN;
                elem[c] = elem[c]->urmator;
                dimensiune--;
                return true;
            }

            // Nodul este ultimul din lista
            else if (curent->urmator == nullptr && curent->precedent != nullptr) {
                curent->precedent->urmator = nullptr;
                curent->precedent = nullptr;
                curent->element.first = INT_MIN;
                curent->element.second = INT_MIN;
                dimensiune--;
                return true;
            }

            // Nodul este în interiorul listei
            else {
                curent->urmator->precedent = curent->precedent;
                curent->precedent->urmator = curent->urmator;
                curent->element.first = INT_MIN;
                curent->element.second = INT_MIN;
                dimensiune--;
                return true;
            }
        }
        curent = curent->urmator;
        if (curent == nullptr)
            break;
    }

    return false;
}

//BC=WC=AC=Theta(1)
int MDO::dim() const {
    return dimensiune;
}

//BC=WC=AC=Theta(1)
bool MDO::vid() const {
    return dimensiune == 0;
}

//BC=WC=AC=Theta(1)
IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

//BC=WC=AC=Theta(1)
/*
* elibereaza memolia alocata dinamica pt listele de noduri
* si pentru vectorii urm si prec
*/
MDO::~MDO() {
    delete[] elem;
    delete[] urm;
    delete[] prec;
}


void MDO::redimensionare() {

    int capNou = capacitate * capacitate;
    int* precNou = new int[capNou];
    Nod** elemNou = new Nod * [capNou];
    int* urmNou = new int[capNou];

    // Copiază valorile din vectorii existenți în cei noi
    for (int i = 0; i < capacitate; i++) {
        urmNou[i] = urm[i];
        precNou[i] = prec[i];
        elemNou[i] = elem[i];
    }

    // Initializează noii vectori cu valorile corespunzătoare elementelor noi
    for (int i = capacitate; i < capNou; i++) {
        urmNou[i] = i + 1;
        precNou[i] = -1;
        Nod* nodCap = new Nod;
        nodCap->element.first = INT_MIN;
        nodCap->element.second = INT_MIN;
        elemNou[i] = nodCap;
    }

    // Actualizează variabilele membru
    urmNou[capNou - 1] = INT_MIN;
    delete[] urm;
    delete[] prec;
    delete[] elem;
    capacitate = capacitate * capacitate;
    elem = elemNou;
    urm = urmNou;
    prec = precNou;
}

