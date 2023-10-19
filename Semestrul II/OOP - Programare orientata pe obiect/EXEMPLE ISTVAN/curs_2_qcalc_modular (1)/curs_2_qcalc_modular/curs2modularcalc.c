//============================================================================
// Name        : modularcalc.cpp
// Author      :
// Version     :
//implements the user interface (console) for the calculator application
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

/**
 * Read a rational number from the console
 * nr - passed by reference, will contain the rational number entered
 */
void readRational(Rational *nr);

/**
 * Print the current total stored in the calculator
 * calc - calculator
 */
void printCurrentTotal(Calculator *calc);

/**
 * Reset the current total to 0
 * calc - calculator
 */
void resetCalculator(Calculator *calc);

/**
 * Read a calculator command from the console
 */
int readCommand();
/**
 * read a number and add to the current total
 * calc - calculator
 */
void addToCalc(Calculator *calc);

int main() {
	Calculator calc;
	resetCalculator(&calc);
	int exit = 0;
	while (!exit) {

		//read a command
		int command = readCommand();
		if (command == 1) {
			//read a number and add to the current total
			addToCalc(&calc);
		} else if (command == 2) {
			resetCalculator(&calc);
			printCurrentTotal(&calc);
		} else if (command == 0) {
			//exit calculator
			exit = 1;
		}
	}
	printf("By by \n");
	return 0;
}

/**
 * read a number and add to the current total
 */
void addToCalc(Calculator *calc) {
	Rational nr;
	readRational(&nr);
	add(calc, nr);	
	printCurrentTotal(calc);

}

/**
 * print out the current total
 */
void printCurrentTotal(Calculator *calc) {
	printf("Total:%d / %d\n", calc->total.a, calc->total.b);
}

/**
 * read in a rational number
 */
void readRational(Rational *nr) {
	printf("Give a:");
	scanf("%d", &nr->a);
	printf("Give b:");
	scanf("%d", &nr->b);
}

/**
 * Read a calculator command from the console
 */
int readCommand() {
	//read a command
	printf("Give a command (2- reset, 1 -add, 0 - exit)");
	int command = 0;
	scanf("%d", &command);
	return command;
}
