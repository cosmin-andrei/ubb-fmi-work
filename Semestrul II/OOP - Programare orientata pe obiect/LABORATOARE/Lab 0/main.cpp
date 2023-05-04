#include <iostream>

using namespace std;

int main()
{
    cout << "Hello, World!" << endl;

    int n,suma=0, nr;
    cout<<"n=";
    cin>>n;
    for(int i=1; i<=n; i++) {
        cin >> nr;
        suma += nr;
    }

    cout<<"suma este "<<suma;
    return 0;
}
