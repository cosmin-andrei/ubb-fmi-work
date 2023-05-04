#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;

// constructor
MDO::MDO(Relatie r) {
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    this->rel = r;
}

// destructor
MDO::~MDO() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// verifica daca MDO este vida
bool MDO::vid() const {
    return this->head == nullptr;
}

// adauga o pereche (cheie, valoare) in MDO
void MDO::adauga(TCheie c, TValoare v) {
    Node* newNode = new Node(c, v);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        count++;
    }
    else {
        Node* current = head;
        while (current != nullptr && !rel(current->key, c)) {
            current = current->next;
        }
        if (current == nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            count++;
        }
        else {
            if (current->prev == nullptr) {
                head->prev = newNode;
                newNode->next = head;
                head = newNode;
                count++;
            }
            else {
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev->next = newNode;
                current->prev = newNode;
                count++;
            }
        }
    }
}

bool MDO::sterge(TCheie c, TValoare v) {
    Node* current = head;
    while (current != nullptr && current->key != c) {
        current = current->next;
    }
    if (current != nullptr) {
        if (current == head && current == tail) {
            head = nullptr;
            tail = nullptr;
            count--;
        }
        else if (current == head) {
            head = current->next;
            head->prev = nullptr;
            count--;
        }
        else if (current == tail) {
            tail = current->prev;
            tail->next = nullptr;
            count--;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            count--;
        }
        delete current;
        return true;
    }
    return false;
}

vector<TValoare> MDO::cauta(TCheie c) const {
    vector<TValoare> values;
    Node* current = head;
    while (current != nullptr && rel(current->key, c)) {
        if (current->key == c) {
            values.push_back(current->value);
        }
        current = current->next;
    }
    return values;
}

IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}