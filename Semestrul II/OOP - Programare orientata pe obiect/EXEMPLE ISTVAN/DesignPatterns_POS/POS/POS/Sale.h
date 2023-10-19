/*
 * Sale.h
 *
 *  Created on: 2012-05-27
 *      Author: istvan
 */

#ifndef SALE_H_
#define SALE_H_
#include <vector>
#include "SaleItem.h"
#include "Product.h"
#include "DiscountPolicy.h"

using namespace std;
class DiscountPolicy;

class Sale {
public:
	Sale(DiscountPolicy* dp) {
		this->discountPolicy = dp;
	}
	/**
	 * Add a sale item to the sale
	 * si - sale item to add
	 */
	void addItem(SaleItem si);

	/**
	 * Add the q products p to the sale
	 * q- quantity > 0
	 * p - product
	 */
	void addItem(int q, Product p);
	/**
	 * Compute the total price for this sale
	 */
	double getTotal();

	~Sale() {
		delete discountPolicy;
	}
private:
	vector<SaleItem> items;
	DiscountPolicy* discountPolicy;
};

#endif /* SALE_H_ */
