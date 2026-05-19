/*#include "Vector.hh"
#include "SList.hh"
#include "dlist.hh"
#include "map.hh"*/
#include "HashTable.hh"
#include "stackk.hh"
#include "rbt.hh"
#include "heap.hh"
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
 HashTable<string, string> ht(20);
    ht.insert("matias", "marquez");
    ht.insert("nicolas", "castaño");
    ht.insert("gustavo", "gutierrez");
     ht.insert("be", "hola");

    /*unsigned int numhash;
        numhash = ht.hashFunction("matias");
        cout << "Hash de clave matias: " << numhash << endl;
         numhash = ht.hashFunction("nicolas");
        cout << "Hash de clave nicolas: " << numhash << endl;
         numhash = ht.hashFunction("gustavo");
        cout << "Hash de clave gustavo: " << numhash << endl;
*/ ht.remove("be");
  auto res = ht.find("be");
  if (res.first) 
  {
    cout <<"El valor de be es: "<< res.second<<endl;
  }else cout <<"be no esta en la tabla";
return 0;
}