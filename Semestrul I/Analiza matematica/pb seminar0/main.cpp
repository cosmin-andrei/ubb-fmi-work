#include <iostream>
using namespace std;
int n;
float f(int k)
{
    if (k<=n)
        return k*k/(6+f(k+1));
    else return 0;
}

int main()
{
    float pi;
    cin>>n;

    pi=3+f(1);
    cout<<pi;

    return 0;
}
