#include "IteratorAB.h"


void IteratorInordine::kpasi(int k) {
   
    if (stivaNoduri.size() < k)
        throw std::exception();
    else if (k <= 0)
        throw std::exception();
    else {

        while (k > 0) {
            //varful stivei
            this->nodCurent = stivaNoduri.top();
            stivaNoduri.pop();

            // verificam daca avem subarbore drept
            if (nodCurent->dr != nullptr) {
                this->nodCurent = this->nodCurent->dr;

                // parcurgem subarborele stang al subarborelui drept
                while (nodCurent != nullptr) {
                    stivaNoduri.push(nodCurent);
                    nodCurent = nodCurent->st;
                }
            }

            //k scade
            k--;
        }
    }
}


/*
* parcurge arborele stang - nod curen - subarbore drept
*/

IteratorInordine::IteratorInordine(const AB& _ab) : ab(_ab) {
   
    while (!this->stivaNoduri.empty()) {
        this->stivaNoduri.pop();
    }

    // parcurge subarborele stâng al arborelui binar
   //plaseazã nodurile în stiva 
    this->nodCurent = this->ab.radacina;
    while (this->nodCurent != NULL) {
        stivaNoduri.push(this->nodCurent);
        this->nodCurent = this->nodCurent->st;
    }

    //verifica sa nu fie stiva goala
    if (!this->stivaNoduri.empty()) {
        this->nodCurent = this->stivaNoduri.top();
    }



}

//initializeaza iteratorul si il seteaza la primul element
//Theta(n)
void IteratorInordine::prim() {
   
    while (!this->stivaNoduri.empty()) {
        this->stivaNoduri.pop();
    }

    // parcurge subarborele stâng al arborelui binar
    //plaseazã nodurile în stiva 
    this->nodCurent = this->ab.radacina;
    while (this->nodCurent != NULL) {
        stivaNoduri.push(this->nodCurent);
        this->nodCurent = this->nodCurent->st;
    }

    //verifica sa nu fie stiva goala
    if (!this->stivaNoduri.empty()) {
        this->nodCurent = this->stivaNoduri.top();
    }
}

//theta(1)
bool IteratorInordine::valid() {
    // de adãugat
    return !stivaNoduri.empty();
}


//theta(1)
TElem IteratorInordine::element() {
    // de adãugat
    if (!valid()) {
        throw exception();
    }
    return nodCurent->valoare;
}

//theta(n)
//parcurgere in adancime a unui arbore binar
void IteratorInordine::urmator() {
    // luam varful stivei si apoi il eliminam
    this->nodCurent = this->stivaNoduri.top();
    this->stivaNoduri.pop();

    //daca nodul curent are un copil drept, facem o traversare in adancime pe subarborele drept al nodului
    //fiecare nod traversat se adauga in stiva.
    if (this->nodCurent->dr != nullptr) {
        this->nodCurent = this->nodCurent->dr;
        while (this->nodCurent != nullptr)
        {
            this->stivaNoduri.push(this->nodCurent);
            this->nodCurent = this->nodCurent->st;
        }
    }

    //daca stiva nu este goala, se ia varful stivei.
    if (!this->stivaNoduri.empty()) {
        this->nodCurent = this->stivaNoduri.top();
    }
    else {
        this->nodCurent = NULL;
    }
}

///////////////////////////////

IteratorPreordine::IteratorPreordine(const AB& _ab) : ab(_ab) {
    //daca stiva nu este goala, o facem sa fie
    while (!this->stivaNoduri.empty()) {
        this->stivaNoduri.pop();
    }
}


//theta(n)
void IteratorPreordine::prim() {

    //nodul curent va deveni radacina arborelui
    this->nodCurent = this->ab.radacina;
}

//theta(1)
bool IteratorPreordine::valid() {
    // de adãugat
    return !stivaNoduri.empty();
}


//theta(1)

TElem IteratorPreordine::element() {
    // de adãugat
    if (!valid()) {
        throw std::exception("Iterator invalid!");
    }
    return stivaNoduri.top()->valoare;
}

//theta(n)
void IteratorPreordine::urmator() {
    // de adãugat
    if (valid()) {
        //daca are copil drept, este adaugat in stiva
        if (this->nodCurent->dr != nullptr)
            this->stivaNoduri.push(this->nodCurent->dr);

        //daca are copil stang, nodul curent devine copilul stang
        if (this->nodCurent->st != nullptr)
            this->nodCurent = this->nodCurent->st;
        
        //daca nodul nu are copil stang si stiva nu e goala, nodul curent devine varful stivei
        else if (!this->stivaNoduri.empty()) {
            this->nodCurent = this->stivaNoduri.top();
            this->stivaNoduri.pop();
        }
        else
            this->nodCurent = nullptr;

    }
    else
        throw std::exception("iterator invalid");
}

///////////////////////////////////

IteratorPostordine::IteratorPostordine(const AB& _ab) : ab(_ab) {
    while (!this->stivaNoduri.empty()) {
        this->stivaNoduri.pop();
    }

    this->nodCurent = ab.radacina;
    while (this->nodCurent != NULL) {
        this->stivaNoduri.push(make_pair(this->nodCurent, false));
        while (this->nodCurent->st != NULL) {
            this->nodCurent = this->nodCurent->st;
            this->stivaNoduri.push(make_pair(this->nodCurent, false));
        }

        this->stivaNoduri.pop();
        this->stivaNoduri.push(make_pair(this->nodCurent, true));

        this->nodCurent = this->nodCurent->dr;
        while (this->nodCurent != NULL && this->nodCurent->st == NULL) {
            this->stivaNoduri.push(make_pair(this->nodCurent, true));
            this->nodCurent = this->nodCurent->dr;
        }
    }

    if (!this->stivaNoduri.empty()) {
        this->nodCurent = this->stivaNoduri.top().first;
        urmator();
    }
}

//theta(n)
void IteratorPostordine::prim() {
    // se goleste stiva
    while (!this->stivaNoduri.empty()) {
        this->stivaNoduri.pop();
    }

    
    this->nodCurent = ab.radacina;//initializez cu rad arbore

    //se parcurge arborele pe ramura stanga, adaugand fiecare nod in stiva
    while (this->nodCurent != NULL) {
        this->stivaNoduri.push(make_pair(this->nodCurent, false));

        while (this->nodCurent->st != NULL) {
            //parcurgem ramura stanga si initializam cu false
            this->nodCurent = this->nodCurent->st;
            this->stivaNoduri.push(make_pair(this->nodCurent, false));
        }

        //nodul curent inainte de a avansa in arbore pe ramura stanga
        this->stivaNoduri.pop();
        this->stivaNoduri.push(make_pair(this->nodCurent, true));


        //nodul curent devine nodul drept si se viziteaza subarborele drept. fiecare nod in stiva
        this->nodCurent = this->nodCurent->dr;
        while (this->nodCurent != NULL && this->nodCurent->st == NULL) {
            this->stivaNoduri.push(make_pair(this->nodCurent, true));
            this->nodCurent = this->nodCurent->dr;
        }
    }

    //nodul curent ia primul element din varful stivei si apeleaza metoda urmator
    if (!this->stivaNoduri.empty()) {
        this->nodCurent = this->stivaNoduri.top().first;
        urmator();
    }

}

//theta(1)
bool IteratorPostordine::valid() {
    // de adãugat
    return !stivaNoduri.empty();
}

//theta(1)
TElem IteratorPostordine::element() {
    // de adãugat
    if (!valid()) {
        throw std::exception("Iterator invalid!");
    }
    return nodCurent->valoare;
}

//theta(n)
void IteratorPostordine::urmator() {
    
    if (valid()) {
        //stiva goala
        if (this->stivaNoduri.empty()) {
            this->nodCurent = nullptr;
            return;
        }

        
        while (true) {
            //luam varful stivei
            auto top = this->stivaNoduri.top();
            this->stivaNoduri.pop();

            //verificam daca nodul a fost deja vizitat
            if (top.second) {
                this->nodCurent = top.first;
                break;
            }

            else {

                //adaugam nodul curent (asociat perechii top) in stiva
                this->nodCurent = top.first;
                this->stivaNoduri.push(make_pair(this->nodCurent, true));
                
                //copil drept
                this->nodCurent = this->nodCurent->dr;

                //se adauga in stiva toti copiii stangi ai nodului curent
                while (this->nodCurent != nullptr) {
                    this->stivaNoduri.push(make_pair(this->nodCurent, false));
                    this->nodCurent = this->nodCurent->st;
                }
            }
        }
    }
}

////////////////////////////////////////////////////

IteratorLatime::IteratorLatime(const AB & _ab) :ab(_ab) {
    //coada devine goala
    while (!this->coadaNoduri.empty()) {
        coadaNoduri.pop();
    }
  
}

//theta(n)
void IteratorLatime::prim() {
    //nodul curent devine radacina arborelui
    this->nodCurent = this->ab.radacina;
}


//theta(1)
bool IteratorLatime::valid() {
    // de adãugat
    return !coadaNoduri.empty();
}

TElem IteratorLatime::element() {
    // de adãugat
    if (!valid()) {
        throw std::exception("Iterator invalid!");
    }

    return coadaNoduri.front()->valoare;
}

void IteratorLatime::urmator() {
    if (!valid()) {
        throw std::exception("Iterator invalid");
    }

    // adauga in coada nodul stang
    if (this->nodCurent->st != NULL) {
        this->coadaNoduri.push(this->nodCurent->st);
    }

    //adauga in coada nodul drept
    if (this->nodCurent->dr != NULL) {
        this->coadaNoduri.push(this->nodCurent->dr);
    }

    //verifica daca coada este goala
    // se extrage primul elem al cozii si devine nodul curent
    if (!this->coadaNoduri.empty()) {
        this->nodCurent = this->coadaNoduri.front();
        this->coadaNoduri.pop();
    }
    else {
        this->nodCurent = NULL;
    }
}
