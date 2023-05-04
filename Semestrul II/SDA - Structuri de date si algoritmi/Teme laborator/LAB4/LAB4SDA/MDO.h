#pragma once
#include <vector>

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

typedef bool(*Relatie)(TCheie, TCheie);

struct Node {
    TCheie key;
    TValoare value;
    Node* prev, * next;
    Node(TCheie k, TValoare v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class MDO {
private:

 
    int count;

    Relatie rel;

public:
    Node* head;
    Node* tail;
    // constructor
    MDO(Relatie r);

    // adauga o pereche (cheie, valoare) in MDO
    void adauga(TCheie c, TValoare v);

    // cauta toate valorile asociate cu o cheie
    std::vector<TValoare> cauta(TCheie c) const;

    // sterge o pereche (cheie, valoare) din MDO
    // returneaza true daca s-a putut sterge, false altfel
    bool sterge(TCheie c, TValoare v);

    // numarul de perechi (cheie, valoare) din MDO
    int dim() const;

    // returneaza true daca MDO-ul e vid, false altfel
    bool vid() const;

    // returneaza un iterator pe MDO
    IteratorMDO iterator() const;

    // destructor
    ~MDO();
};
