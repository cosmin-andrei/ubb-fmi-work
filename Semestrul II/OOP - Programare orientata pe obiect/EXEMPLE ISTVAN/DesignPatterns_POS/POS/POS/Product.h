
#ifndef PRODUCT_H_
#define PRODUCT_H_
#include <string>
using namespace std;

/**
 * Model a product form the POS application
 *
 */
class Product {
public:
	Product(int id, string desc, string type, double price) {
		this->code = id;
		this->description = desc;
		this->type = type;
		this->price = price;
	}
	/**
	 * Copy constructor
	 */
	Product(const Product& p) {
		this->code = p.code;
		this->description = p.description;
		this->type = p.type;
		this->price = p.price;
	}
	Product() {
		this->code = 0;
	}
	int getCode() {
		return code;
	}
	string getDescription() const {
		return description;
	}
	string getType() const {
		return type;
	}
	double getPrice() const{
		return price;
	}
private:
	int code;
	double price;
	string description;
	string type;
};

#endif /* PRODUCT_H_ */
