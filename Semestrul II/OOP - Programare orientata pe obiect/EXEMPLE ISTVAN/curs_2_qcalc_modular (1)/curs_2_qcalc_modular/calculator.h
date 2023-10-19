
/*
 * calculator.h
 * Calculator functinalities
 */
#include "rational.h"

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

/**
 * Store the calculator total
 */
typedef struct {
	Rational total; //stores the current total
	Rational memory; //user can store values away
} Calculator;

/**
 * Add a rational number to the current total
 * calc - calculator
 * nr rational number
 */
void add(Calculator *calc, Rational nr);

/**
 * Reset the current total to 0
 * calc - calculator
 */
void resetCalculator(Calculator *calc);

/**
 * Return the current total
 * calc - Calculator
 */
Rational getCurrentTotal(Calculator *calc);

void testCalculator();

#endif /* CALCULATOR_H_ */
