#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"


/*
* TAD  MultiDictionar  ordonat-reprezentare  sub  forma  unei  LDI  de cheidistincte  ordonate  în raport cu o relație de ordine R între chei. 
Fiecare cheie va memora o LDI cu valorile asociate cheii
Reprezentarea înlănțuirilor pe tablou dinamic
*/

int main() {
    testAll();
    testAllExtins();
    std::cout << "Finished Tests!" << std::endl;
}
