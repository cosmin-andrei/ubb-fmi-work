/*
 * utils.cpp
 * Utility functions
 */
#include "utils.h"


/**
 * Computes the greatest common divisor of two positive integers.
 * a, b integers, a,b>0
 * return the the greatest common divisor of a and b.
 */
int gcd(int a, int b) {
	if (a == 0 || b == 0) {
		return a + b;
	}
	while (a != b) {
		if (a > b) {
			a = a - b;
		} else {
			b = b - a;
		}
	}
	return a;
}
/**
 * test function for gdc
 */
void testgdc() {
	assert(gcd(3,9)==3);
	assert(gcd(3,4)==1);
	assert(gcd(9,15)==3);
}
