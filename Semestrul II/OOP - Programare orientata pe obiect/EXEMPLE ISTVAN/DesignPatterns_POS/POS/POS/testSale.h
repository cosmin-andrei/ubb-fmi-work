/*
 * testSale.h
 *
 *  Created on: 2012-05-27
 *      Author: istvan
 */

#include "Sale.h"
#include "Product.h"
#include "SaleItem.h"
#include "NoDiscount.h"
#include <string>
#include <assert.h>
void testSale() {
	Sale s(new NoDiscount());
	Product p1(1, "Apple", "food", 2.0);
	Product p2(1, "TV", "electronics", 2000.0);
	s.addItem(3, p1);
	s.addItem(1, p2);
	assert(s.getTotal()==2006);

	Sale s2(new CreditCardDiscount());
	s2.addItem(3, p1);
	s2.addItem(1, p2);
	//total with discount for card
	assert(s2.getTotal()==1965.88);
}

void testSaleC() {

	Sale s(new NoDiscount());
	Product p1(1, "Apple", "food", 10.0);
	Product p2(2, "TV", "electronics", 2000.0);
	s.addItem(3, p1);
	s.addItem(1, p2);
	assert(s.getTotal()==2030);

	CompoundDiscount* cD = new CompoundDiscount();
	cD->addPolicy(new CreditCardDiscount());
	cD->addPolicy(new QuantityDiscount());


	Sale s2(cD);
	s2.addItem(2, p1);
	s2.addItem(3, p2);
	//total with discount for card
	assert(s2.getTotal() ==5299.6);
}

