/*
 * rational.h
 *
 *  Created on: 2012-03-04
 *      Author: istvan
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

/**
 * New data type to store rational numbers
 */
typedef struct {
	int a, b;
} Rational;

/**
 * Compute the sum of 2 rational numbers
 * a,b rational numbers
 * rez - a rational number, on exit will contain the sum of a and b
 */
void sum(Rational nr1, Rational nr2, Rational *rez);

#endif /* RATIONAL_H_ */

