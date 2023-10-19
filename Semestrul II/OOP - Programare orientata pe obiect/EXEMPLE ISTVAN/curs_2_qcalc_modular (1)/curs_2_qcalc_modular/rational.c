/*
 * rational.cpp
 * Implement rational number related functionalities
 */
#include "rational.h"
#include "utils.h"
/**
 * Sum of 2 rational number
 */
void sum(Rational nr1, Rational nr2, Rational* rez){
	rez->a = nr1.a * nr2.b + nr1.b * nr2.a;
	rez->b = nr1.b * nr2.b;
	int d = gcd(rez->a, rez->b);
	rez->a = rez->a / d;
	rez->b = rez->b / d;
}

