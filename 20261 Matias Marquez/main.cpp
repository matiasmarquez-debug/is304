//#include "Vector.hh"
#include "LIST.hh"
#include "dlist.hh"
#include "map.hh"
#include <iostream>
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

string paroimpar ( int num){
    if (num%2==0) return "par";
    return "impar";
}
int main() {
    Map<string, int> m;
    m.insert("juan", 1);
    m.insert("samuel", 2);
    m.insert("nicolas", 3);
    m.insert("anhai", 4);
    m.insert("matias", 5);
    m.insert("mateo", 6);
    m.print();
    //cout<<m.search("nicolas")<<endl;
    Map<string, int> j(m);
    j.print();
    m.remove("nicolas");
    m.print();
    
    //cout<<"El valor de matias es: "<<m.search("matias")<<endl;
return 0;
}