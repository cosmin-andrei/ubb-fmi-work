
#include "stdafx.h"

#include "NoDiscount.h"
/**
 * Compute the sum of all discounts
 */
double CompoundDiscount::getDiscount(const Sale* s, SaleItem si) {
	double discount = 0;
	for (auto policy: policies) {
		discount += policy->getDiscount(s, si);
	}
	return discount;
}
