#include "Vector.hh"
#include "LIST.hh"
#include "dlist.hh"
#include "map.hh"
#include <iostream>
using namespace std;
bool isEven(int num) {
    return num % 2 == 0;
}

int morethanfive(int num) {
    if (num > 5) 
        return num;
        return 0;
}

int morethan5(int num) {
        return num>5;
}


void paroimpar ( int num){
    if (num%2==0) cout<<"par"<<endl;
    cout<<"impar"<<endl;
}

void aumentar(int& v) {
    v = v+5;
}

int main() {
  
return 0;
}