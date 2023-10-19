// POS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "testSale.h"
#include <thread>
#include <iostream>

void func1(int n) {
	for (int i = 0; i < n; i++) {
		std::cout << i << "\n";
	}
}

void sampleThreads() {
	std::thread t1{ func1,1000 };
	std::thread t2{ func1,1000 };
	t1.join();
	t2.join();
}
int main()
{
	//sampleThreads();
	testSale();
	testSaleC(); 
    return 0;
}

