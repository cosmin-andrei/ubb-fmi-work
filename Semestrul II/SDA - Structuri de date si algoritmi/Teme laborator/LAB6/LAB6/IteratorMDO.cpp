#include "IteratorMDO.h"
#include "MDO.h"

//BC=WC=AC=Theta(n)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    /* de adăugat */
    prim();
}

//BC=WC=AC=Theta(n)
void IteratorMDO::prim() {
    /* de adăugat */
    curentLista = 0; //indicele listei
    curentNod = dict.l[curentLista];//Se obține primul nod din lista corespunzătoare indicei curent
    
    // Se parcurg listele până când se ajunge la o listă nevidă sau se depășește numărul total de liste
    while (curentLista < dict.m && curentNod == nullptr) {
        curentLista++;
        if (curentLista < dict.m)
            curentNod = dict.l[curentLista]; // Se obține primul nod din lista corespunzătoare noii liste curente
    }
}

void IteratorMDO::urmator() {
    /* de adăugat */
    if (valid()) {
        curentNod = curentNod->urm;
        //Se parcurg listele până când se ajunge la o listă nevidă sau se depășește numărul total de liste
        while (curentLista < dict.m && curentNod == nullptr) {
            curentLista++;
            if (curentLista < dict.m)
                curentNod = dict.l[curentLista]; // Se obține primul nod din lista corespunzătoare noii liste curente
        }
    }
    else
        throw exception();
}

//BC=Wc=AC=Theta(1)
bool IteratorMDO::valid() const {
    /* // Returnează adevărat dacă iteratorul este într-o poziție validă, adică nu a depășit numărul total de liste și nodul curent nu este nullptr */
    return curentLista < dict.m && curentNod != nullptr;
}

//BC=WC=AC=Theta(1)
TElem IteratorMDO::element() const {
    /* de adăugat */
    if (valid()) {
        return curentNod->e;
    }
    else
        throw exception();
}