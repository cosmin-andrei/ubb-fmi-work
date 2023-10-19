#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

//initializam membrii clasei
//BC=WC=AC=Theta(1)
// m - dimensiunea unei tabele hash, l vector de pointeri la liste cu m elemente nule
MDO::MDO(Relatie r) {
    m = MAX; // inițializăm m cu o valoare predefinită
    rel = r;
    l = vector<PNod>(m, nullptr); // inițializăm vectorul de liste cu m elemente nule
}

//BC=Theta(1)
//AC=WC=Theta(n)
/*
Se creeza o noua pereche e (cu cheie si valoare)
determinam indecele i din tabela hash pt cheia c
se creeaza un nod p cu perechea e si se insereaza in ordinea corecta a cheilor
*/
void MDO::adauga(TCheie c, TValoare v) {
    TElem e = pair<TCheie, TValoare>(c, v);
    int i = d(c); // Se calculează indicele în funcție de cheie
    PNod p = new Nod(e, nullptr);

    if (l[i] == nullptr) {
        l[i] = p; // Dacă lista la indicele i este goală, nodul p devine capul listei
    }
    else {
        PNod pre = nullptr; // Se inițializează un pointer la nodul precedent cu nullptr
        PNod curent = l[i]; // Se obține capul listei

        // Se parcurge lista până când se găsește un nod cu cheia mai mare decât cheia curentă sau se ajunge la sfârșitul listei
        while (curent != nullptr && rel(curent->e.first, c)) {
            pre = curent;
            curent = curent->urm;
        }

        // Dacă nodul precedent este nullptr, înseamnă că nodul p trebuie adăugat la începutul listei
        if (pre == nullptr) {
            p->urm = l[i];
            l[i] = p; // p devine capul liste
        }
        else {
            p->urm = curent; // Nodul p este adăugat la începutul listei
            pre->urm = p;
        }
    }
}

/*
* se creeaza vectorul vec si se parcurge lista pentru fiecare nod care are cheia c
*/
//BC=AC=WC=Theta(n)
vector<TValoare> MDO::cauta(TCheie c) const {
    vector<TValoare> vec;
    PNod parcurg = l[d(c)];

    while (parcurg != nullptr) {
        if (parcurg->e.first == c) {
            vec.push_back(parcurg->e.second); // Se adaugă valoarea în vectorul vec
        }
        parcurg = parcurg->urm;
    }

    return vec;
}

/*
* Sterge o pereche cheie-valoare din MDO
* daca nodul este gasit se returneaza true si se elimina
* false altfel
*/
//BC=AC=WC=Theta(n)
bool MDO::sterge(TCheie c, TValoare v) {

    PNod q1 = nullptr; // Se inițializează un pointer la nodul precedent cu nullptr
    PNod q = l[d(c)]; // Se obține capul listei corespunzătoare cheii c

    while (q != nullptr) {
        // Se verifică dacă nodul curent conține perechea cheie-valoare căutată
        if (q->e.first == c && q->e.second == v) {
            break;
        }
        q1 = q; // Se avansează pointerul la nodul precedent
        q = q->urm; // Se avansează pointerul la nodul curent
    }

    //daca nodul a fost gasit
    if (q != nullptr) {
        if (q == l[d(c)]) {
            l[d(c)] = l[d(c)]->urm; // Se actualizează capul listei cu următorul nod
            delete q;
        }
        else {
            q1->urm = q->urm;
            delete q;
        }

        return true;
    }

    return false;
}

//BC=AC=WC=Theta(n)
int MDO::dim() const {
    int d = 0;

    for (int i = 0; i < m; i++) {
        PNod parcurg = l[i];
        while (parcurg != nullptr) {
            d++; // Se incrementează contorul
            parcurg = parcurg->urm;
        }
    }

    return d;
}

//WC=AC=Theta(n)
//BC=Theta(1)
bool MDO::vid() const {
    for (int i = 0; i < m; i++) {
        if (l[i] != nullptr) {
            return false;
        }
    }

    return true;
}

//BC=Wc=AC=Theta(1)
IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

//BC=AC=WC=Theta(n)
MDO::~MDO() {
    for (int i = 0; i < m; i++) {
        while (l[i] != nullptr) {
            PNod p = l[i];
            l[i] = l[i]->urm;
            delete p;
        }
    }
}

//BC=WC=AC=Theta(n)
int MDO::adaugaInexistente(MDO& mdo) {
    int numarPerechiAdaugate = 0;

    IteratorMDO itMDO = mdo.iterator();
    while (itMDO.valid()) {
        TElem pereche = itMDO.element();
        TCheie cheie = pereche.first;
        TValoare valoare = pereche.second;

        // Verificăm dacă perechea există deja în MDO
        if (mdo.cauta(cheie).empty()) {
            // Perechea nu există, o adăugăm în MDO
            mdo.adauga(cheie, valoare);
            numarPerechiAdaugate++;
        }

        itMDO.urmator();
    }

    return numarPerechiAdaugate;
}