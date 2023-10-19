/*
 * calculator.cpp
 * Implements Functionalities related to a calculator
 */
#include "calculator.h"
#include "rational.h"
/**
 * Add a rational number to the current total
 * nr rational number
 */
void add(Calculator *calc, Rational nr) {
	sum(calc->total, nr, &calc->total);
}

/**
 * Return the current total
 * calc - Calculator
 */
Rational getCurrentTotal(Calculator *calc) {
	return calc->total;
}
/**
 * Reset the current total to 0
 * calc - calculator
 */
void resetCalculator(Calculator *calc) {
	calc->total.a = 0;
	calc->total.b = 1;
}

void testCalculator() {

}
