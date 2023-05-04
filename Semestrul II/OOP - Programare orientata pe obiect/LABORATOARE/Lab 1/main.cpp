/*
Aplicatia ofera un mic meniu pentru a efectua repetat operatia ceruta.
Programul trebuie sa contina cel putin 2 functii. (functia main+ 1,2 functii)
Fiecare funtie trebuie specificata. Specificatia contine: a scurta descriere, descrierea parametrilor,
conditii impuse asupra datelor de intrare (preconditii), descriere rezultatului (post conditii)

10.  Tipareste un numar precizat de sume partiale din dezvoltarea
 sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...

 2. Genereaza primele n (n natural dat) numere prime
 */

#include <iostream>
#include <cmath>

void sume_partiale();

void prime();

using namespace std;

void meniu()
{
    /*
     * functia afiseaza meniul
     */
    short int comanda;
    cout<<"Alege una dintre optiuni (1 sau 2):"<<endl;
    cout<<"1. Tipareste un numar precizat de sume partiale din dezvoltarea sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ..."<<endl;
    cout<<"2. Genereaza primele n numere prime\n\n";
    cout<<"Introdu optiunea: ";
    cin>>comanda;

    if(comanda==1)
        sume_partiale();
    else if(comanda==2)
        prime();
    else
        {cout<<"Comanda incorecta"<<endl;
            meniu();}
}

double factorial(int n)
{
    /*
     calculeaza n factorial
     params: n - tip int
     preconditii: n>0

     return: rez - double
     */

    double rez = 1;
    for(int i=1; i<=n; i++)
        rez *= i;

    return rez;

}

bool verifica_prim(unsigned int nr)
{
    /*
     * functia verifica in mod eficient daca numarul dat este prim
     *
     * params: nr - unsigned int
     * preconditii: nr>0
     *
     * return True, daca numarul este prim
     * return False, daca numarul nu este prim
     */
    for (unsigned int d=2; d<=nr/2; d++)
        if(nr%d==0) return false;

    return true;
}

void prime() {

    /*
     * functia genereaza primele n numere date
     *
     * n este un numar int cu 12 cifre
     */
    unsigned int n, k=0, nr=2;
    cout<<"Introdu numarul de numere prime pe care doresti sa il generezi: ";
    cin>>n;

    while(k<n)
    {
        if(verifica_prim(nr) == true) {
            cout<<nr<<" ";
            k++;
        }
        nr++;
    }


}

void sume_partiale() {

    /*
     * functia calculeaza sumele partiale si le afiseaza pe ecran
     *
     * params: -
     */

    double x;
    int n;

    /*
        x - double, n - int
        preconditii: n > 0
     */

    cout << "Introduceti unghiul x in radiani: ";
    cin >> x;

    cout << "Introduceti numarul de sume partiale n: ";
    cin >> n;

    //calcul sume partiale
    double suma = 0;
    for (int i = 0; i < n; i++) {

        double term = pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        suma += term;
        cout << "Suma partiala " << i + 1 << " este " << suma << endl;
    }
}


int main()
{
    meniu();
    return 0;
}
