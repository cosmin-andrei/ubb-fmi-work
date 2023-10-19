/*
 * DiscountPolicy.h
 *
 *  Created on: 2012-05-27
 *      Author: istvan
 */

#ifndef DISCOUNTPOLICY_H_
#define DISCOUNTPOLICY_H_
#include "Sale.h"
#include "SaleItem.h"
class Sale;
/**
 * Discount Policy for computing the total of a sale
 */
class DiscountPolicy {
public:
	/**
	 * Compute the discount for the sale item
	 * s - the sale, some discount may based on all the products in te sale, or other attributes of the sale
	 * si - the discount amount is computed for this sale item
	 * return the discount amount
	 */
	virtual double getDiscount(const Sale* s, SaleItem si)=0;
	virtual ~DiscountPolicy() {
	}

};

#endif /* DISCOUNTPOLICY_H_ */
