#include "IteratorVectorDinamic.h"
#include "VectorDinamic.h"


IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& _v) :
		v(_v) {
}

void IteratorVectorDinamic::prim() {
}

bool IteratorVectorDinamic::valid() const{
	return false;
}

TElem IteratorVectorDinamic::element() const{
	return -1;
}

void IteratorVectorDinamic::urmator() {
}