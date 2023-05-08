#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	curentIndex = 0;
	curent = dict.head;
	if (curent == nullptr || curent->prev != nullptr) {
		curent = nullptr;
	}
	else {
		while (curent->next != nullptr && dict.rel(curent->key, curent->next->key)) {
			curent = curent->next;
		}
	}
}

void IteratorMDO::prim() {
	curentIndex = 0;
	curent = dict.head;
	if (curent == nullptr || curent->prev != nullptr) {
		curent = nullptr;
	}
	else {
		while (curent->next != nullptr && dict.rel(curent->key, curent->next->key)) {
			curent = curent->next;
		}
	}
}

void IteratorMDO::urmator() {
	if (!valid()) {
		throw std::exception("Nu exista urmator");
	}
	if (curent->next != nullptr) {
		curent = curent->next;
		if (dict.rel(curent->prev->key, curent->key)) {
			curentIndex++;
		}
	}
	else {
		curent = nullptr;
	}
}

bool IteratorMDO::valid() const {
	return curent != nullptr && curentIndex < dict.count;
}

TElem IteratorMDO::element() const {
	if (!valid()) {
		throw std::exception("Nu exista element");
	}
	return std::make_pair(curent->key, curent->value);
}
