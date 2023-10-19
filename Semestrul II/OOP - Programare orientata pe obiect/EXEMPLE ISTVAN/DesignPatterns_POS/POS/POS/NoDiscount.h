

#ifndef NODISCOUNT_H_
#define NODISCOUNT_H_
#include <vector>
#include "Sale.h"
#include "SaleItem.h"
#include "DiscountPolicy.h"
class Sale;

class NoDiscount: public DiscountPolicy {
public:
	double getDiscount(const Sale* s, SaleItem si) {
		return 0;
	}

};

/**
 * Apply 2% discount
 */
class CreditCardDiscount: public DiscountPolicy {
public:

	virtual double getDiscount(const Sale* s, SaleItem si) {
		return si.getQuantity() * si.getProduct().getPrice() * 0.02;
	}

};
/**
 * Apply 10% discount for products with quantity  3 or more on a sale
 */
class QuantityDiscount: public DiscountPolicy {
	virtual double getDiscount(const Sale* s, SaleItem si) override {
		if (si.getQuantity() >= 3) {
			return si.getQuantity() * si.getProduct().getPrice() * 0.1;
		}
		return 0;
	}
};
/**
 * Combine multiple discount types
 * The discounts will sum up
 */
class CompoundDiscount: public DiscountPolicy {
public:
	virtual double getDiscount(const Sale* s, SaleItem si) override;

	void addPolicy(DiscountPolicy* p) {
		policies.push_back(p);
	}
	~CompoundDiscount() {
		for (auto pol : policies) {
			delete pol;
		}
	}
private:
	vector<DiscountPolicy*> policies;
};
#endif /* NODISCOUNT_H_ */
