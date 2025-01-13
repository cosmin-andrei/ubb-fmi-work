#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cstdlib>

using namespace std;

void generateNumbers(int count) {
    char* filename = "numbers.txt";
    ofstream out(filename);

    // Utilizez timpul curent pentru randomizare
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    out << count << '\n';
    // Generez numere și le pun în fișier
    for (int i = 0; i < count; i++) {
        int numDigits = rand() % 5 + 1; // Generează un număr de cifre între 1 și 5
        int num = 0;
        for (int j = 0; j < numDigits; j++) {
            int digit = rand() % 10;
            num = num * 10 + digit;
        }
        out << num << " ";
    }
    out.close();
}