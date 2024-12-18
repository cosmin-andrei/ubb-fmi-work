/*
============================================================================
Name        : curs2proceduralcalc.c
Author      :
Version     :
Copyright   : Your copyright notice
Description : Hello World in C, Ansi-style
============================================================================
*/

#include <assert.h>
#include <stdio.h>
//include for abs
#include <stdlib.h>


//represent a rational number
typedef struct {
	int m;
	int n;
} RationalNr;

/*
* greatest common divisor .
* Pre: a, b >= 0, a*a + b*b != 0
* return gcd
*/
int gcd(int a, int b) {
	a = abs(a);
	b = abs(b);
	if (a == 0 || b == 0) {
		return a + b;
	}
	while (a != b) {
		if (a > b) {
			a = a - b;
		}
		else {
			b = b - a;
		}
	}
	return a;
}
/*
* Sum of rational numbers
* rez,rn rational numbers
* Post: rez = rez+rn
*/
void add(RationalNr* rez, RationalNr rn) {
	rez->m = rez->m * rn.n + rez->n * rn.m;
	rez->n *= rn.n;
	int gcdTo = gcd(rez->m, rez->n);
	rez->m = rez->m / gcdTo;
	rez->n = rez->n / gcdTo;
}

void testAdd() {
	RationalNr r1 = { .m = 1,.n = 2 };
	RationalNr r2 = { .m = 1,.n = 2 };
	add(&r1, r2);
	assert(r1.n == 1);
	assert(r1.m == 1);
}

/**
* Test function for gcd
*/
void test_gcd() {
	assert(gcd(2, 4) == 2);
	assert(gcd(3, 27) == 3);
	assert(gcd(7, 27) == 1);
	assert(gcd(7, -27) == 1);
	assert(gcd(7, 0) == 7);
}

void allTests() {
	test_gcd();
	testAdd();
}

void runApp() {
	RationalNr total = { 0, 1 };
	while (1) {
		printf("Enter m/n to add\n");
		RationalNr rn;
		scanf("%d", &rn.m);
		scanf("%d", &rn.n);
		if (rn.n == 0) break;
		add(&total, rn);
		printf("Total: %d/%d\n", total.m, total.n);
	}
}

int main() {

	allTests();

	runApp();
	
	return 0;
}