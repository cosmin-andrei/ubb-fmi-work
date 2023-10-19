/*
 * Sale.cpp
 *
 *  Created on: 2012-05-27
 *      Author: istvan
 */
#include "stdafx.h"

#include "Sale.h"

void Sale::addItem(int q, Product p) {
	SaleItem si(q, p);
	this->addItem(si);
}

/**
 * Add a sale item to the sale
 * si - sale item to add
 */
void Sale::addItem(SaleItem si) {
	items.push_back(si);
}

///**
// * Compute the total price for this sale
// */
//double Sale::getTotal() {
//	double total = 0;
//	for (int i = 0; i < items.size(); i++) {
//		SaleItem sIt = items[i];
//		double price = sIt.getQuantity() * sIt.getProduct().getPrice();
//		total += price;
//	}
//	return total;
//}

/**
 * Compute the total price for this sale
 * return the total for the items in the sale
 */
double Sale::getTotal() {
	double total = 0;
	for (const SaleItem& sIt :items) {		
		double price = sIt.getQuantity() * sIt.getProduct().getPrice();
		//apply discount
		price -= discountPolicy->getDiscount(this, sIt);
		total += price;
	}
	return total;
}
