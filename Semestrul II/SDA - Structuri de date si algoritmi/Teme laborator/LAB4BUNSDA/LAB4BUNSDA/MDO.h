#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

struct Node {
    TCheie key;
    TValoare value;
    int prevIndex;
    int nextIndex;
    Node(TCheie k, TValoare v, int p = -1, int n = -1) : key(k), value(v), prevIndex(p), nextIndex(n) {}
};

class MDO {
    friend class IteratorMDO;
private:
    vector<Node> nodes;
    int headIndex;
    int tailIndex;
    int count;
    Relatie rel;

public:
    // constructorul implicit al MultiDictionarului Ordonat
    MDO(Relatie r);

    // adauga o pereche (cheie, valoare) in MDO
    void adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    //sterge o cheie si o valoare 
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    //returneaza numarul de perechi (cheie, valoare) din MDO 
    int dim() const;

    //verifica daca MultiDictionarul Ordonat e vid 
    bool vid() const;

    // se returneaza iterator pe MDO
    // iteratorul va returna perechile in ordine in raport cu relatia de ordine
    IteratorMDO iterator() const;

    // destructorul 
    ~MDO();
};
