
#ifndef SALEITEM_H_
#define SALEITEM_H_
#include "Product.h"
class SaleItem {
public:
	/**
	 * Create a sale item
	 * q - quantity, number of products of the same type
	 * p - product
	 */
	SaleItem(int q, Product p) {
		this->quantity = q;
		this->p = p;
	}

	/**
	 * Copy constructor
	 */
	SaleItem(const SaleItem& si) {
		this->quantity = si.quantity;
		this->p = si.p;
	}

	int getQuantity() const{
		return quantity;
	}

	Product getProduct() const{
		return p;
	}
private:
	int quantity;
	Product p;

};

#endif /* SALEITEM_H_ */
