//#include "Vector.hh"
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

float promedio(int suma, int tamano)
{
    
}

void paroimpar ( int num){
    if (num%2==0) cout<<"par"<<endl;
    cout<<"impar"<<endl;
}

void aumentar(int& v) {
    v = v+5;
}

int main() {
    Map<string, int> m;
    m.insert("juan", 1);  //3
    m.insert("samuel", 2);  //6
    m.insert("nicolas", 3);  //5
    m.insert("camilo", 6); //2
    m.insert("matias", 5);  //4
    m.insert("ana", 4);   //1
    m.insert("valeria",7);
    m.print();

   m.preorden(paroimpar);
  
    //cout<<m.find("nicolas", 0)<<endl;
//    Map<string, int> j(m);

  //  j.print();
   // m.remove("nicolas");
    //m.print();
    
    //cout<<"El valor de matias es: "<<m.search("matias")<<endl;
return 0;
}