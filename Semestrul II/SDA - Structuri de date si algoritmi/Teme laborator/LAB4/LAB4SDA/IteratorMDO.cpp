#include "IteratorMDO.h"
#include "MDO.h"
#include <stdexcept>

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    prim();
}

void IteratorMDO::prim() {
    curent = dict.head;
    if (curent != nullptr) {
        urm = curent->next;
    }
}

void IteratorMDO::urmator() {
    if (urm == nullptr) {
        throw std::runtime_error("Nu exista urmator");
    }
    curent = urm;
    urm = urm->next;
}

bool IteratorMDO::valid() const {
    return curent != nullptr;
}

TElem IteratorMDO::element() const {
    if (curent == nullptr) {
        throw std::runtime_error("Nu exista element");
    }
    return curent->value;
}
