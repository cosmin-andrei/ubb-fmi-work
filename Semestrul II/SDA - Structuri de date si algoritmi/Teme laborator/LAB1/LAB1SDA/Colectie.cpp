//
// Created by Cosmin on 4/3/2023.
//
#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include<iostream>


// best case, worst case, average case = Theta(1)
Colectie::Colectie() {

    //constructor clasa Colectie

    this->n = 0; //numarul de elemente
    this->cp = 1; // capacitatea
    
    this->first = INT_MAX;
    this->last = INT_MIN;

    elems = new TElem[1]; // alocam spatiu pt vector
}

//best case, wc, ac = Theta(n)
void Colectie::redim() {
    
    //redimensionam vectorul de frecvente prin dublarea capacitatii

    cp *= 2; // dublam capacitatea

    //alocam spatiu

    TElem* elemsNou;
    elemsNou = new TElem[cp];
    
    //copiem vechile valori in zona noua
    for (int i = 0; i < cp; i++)
        elemsNou[i] = elems[i];

    //eliberam vechea zona
    delete[] elems;

    //indicam spre noua zona
    elems = elemsNou;

}

// best case - theta(1)
// wc, ac - Theta(n)
void Colectie::adauga(TElem elem) {
    
    //adauga elementul elem in colectie

    if (n == 0) {
        first = elem;
        last = elem;
        n = 1;
        elems[0] = 1;
    }
    else {
        while (elem < first && last - elem + 1 >= cp)
            redim();
        while (elem > last && elem - first + 1 >= cp)
            redim();
        if (elem < first) {
            for (int i = n - 1; i >= 0; i--)
                elems[i + first - elem] = elems[i];
            for (int i = 0; i < first - elem; i++)
                elems[i] = 0;
            first = elem;
            n = last - first + 1;
            elems[elem - first] = 1;
        }
        else if (elem > last) {
            for (int i = n; i < elem - first + 1; i++)
                elems[i] = 0;
            last = elem;
            n = last - first + 1;
            elems[elem - first] = 1;
        }
        else
            elems[elem - first]++;
    }

}


//bc, wc, ac = Theta(1)
bool Colectie::sterge(TElem elem) {
    
    //sterge elementul elem din colectie

    if (n == 0 || elem<first || elem>last)
    {
        return false;
    }
    int index = elem - first;

    if (elems[index] == 0)
    {
        return false;
    }

    if (elems[index] > 0)
    {
        elems[index]--;
        return true;
    }

    return false;
}

//bc, wc, ac = Theta(1)
bool Colectie::cauta(TElem elem) const {
    
    //cauta elementul elem in colectie
    
    if (elem<first || elem>last)
        return false;

    int index = elem - first;

    if (elems[index] != 0)
        return true;

    return false;
}

//bc, wc, ac = Theta(1)
int Colectie::nrAparitii(TElem elem) const {

    //returneaza nr de aparitii ale elementului elem in colectie

    if (elem<first || elem>last)
        return 0;

    return elems[elem-first];
}

//bc, wc, ac = Theta(n)
int Colectie::dim() const {

    //returneaza dimensiunea colectiei

    int k = 0;
    for (int i = 0; i < n; i++) {
        k += elems[i];
    }
    return k;
}

int Colectie::dimVect() const {
    //dimensiunea vectorului de frecvente
    return n;
}

//bc, wc, ac = Theta(1)
bool Colectie::vida() const {
    //true daca colectia este vida
    return n == 0;
}

//bc, wc, ac = Theta(1)
IteratorColectie Colectie::iterator() const {
    return  IteratorColectie(*this);
}

//bc, wc, ac = Theta(1)
Colectie::~Colectie() {
    //elibereaza spatiul alocat vectorului elems
    delete[] elems;
}

//bc,wc,ac=Theta(n)
int Colectie::transformaInMultime() {
    
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (nrAparitii(elems[i]) > 1)
         while(nrAparitii(elems[i])>1)   
         {
            sterge(elems[i]);
            k = k + 1;
         }

    }
    return k;

}