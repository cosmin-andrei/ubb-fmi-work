#include <iostream>
using namespace std;

void raza(){
    float r;
    float pi;
    pi = 3.14;
    cin>>r;

    float p;
    p= 2 * pi * r;

    float a;
    a= pi * r * r;

    cout<<p;
    cout<<" ";
    cout<<a;

}

void cmmdc(){
    int a;
    int b;
    cin>>a;
    cin>>b;

    while(a!=b){
        if(a>b){
            a=a-b;
        }else{
            b=b-a;
        }
    }

    cout<<a;
}

void suma(){
    int n;
    cin>>n;

    int k;
    k=0;

    int s;
    s=0;

    while(k<n){
        int nr;
        cin>>nr;

        s=s+nr;
        k=k+1;
    }

    cout<<s;
}

int main() {
    raza();
//    cmmdc();
//    suma();
    return 0;
}
