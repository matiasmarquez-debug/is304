#include "Vector.hh"
#include "LIST.hh"
#include "dlist.hh"
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
Dlist<int> l;
l.push_back(3);l.push_back(3);l.push_back(7);   l.push_back(9);l.push_back(9);   l.push_back(9);l.push_back(6);   l.push_back(8);   l.push_back(8);   
l.print();  
l.unique();
l.print(); 
return 0;
}