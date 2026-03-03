#include "Vector.hh"
#include <iostream>
int main() {
 Vector<int> v;
v.push_back(4); v.push_back(2); v.push_back(1); v.push_back(3);
 Vector<int> z;
 z.push_back(5); z.push_back(9); z.push_back(4); z.push_back(6);
 v.append(z);
 v.print();
 v.slice(3,6).print();
 v.operator=(z);
 v.print();
/*//Exercise 1.3 - Strings
    Vector<string> v(5); 
    v.push_back("the"); v.push_back("quick"); v.push_back("brown"); v.push_back("fox");
    v.push_back("jumps");
  v.print();
  cout<<"size: "<<v.size()<<endl;
  cout<<"capacity: "<<v.capacity()<<endl;
  cout<<"Popfront and popback"<<endl;
  v.pop_back();
  v.pop_front();
  v.print();
  cout<<"size: "<<v.size()<<endl;
  cout<<"capacity: "<<v.capacity()<<endl;
   cout<<"Insert 99 at index 2"<<endl;
   v.insert("99",2);
   v.print();
*/
/*
//Exercise 1.2 -Access methods 
Vector<int> v(5); 
int num = 5;
for (int i = 0 ; i < 5; i++)
{v.push_back(num);
num= num+5;}
cout<<"FRONT: "<< v.front()<<endl;
cout<<"Back: "<< v.back()<<endl;
cout<<"the middle element: "<<v.at(2)<<endl;
v[2]=100;
v.print();

 // the function "at" its safer than the function "operator" 
 //but the operator is faster than at because it doesnt have a bound check.
 // I prefer the at because it can prevent errors
*/

/*Exercise 1.1 - Basicoperations
    Vector<int> v; 
    for(int i = 0; i < 10; i++) {
        v.push_back(i + 1);
    }
  v.print();
  cout<<"size: "<<v.size()<<endl;
  cout<<"capacity: "<<v.capacity()<<endl;

  cout<<"Popfront and popback"<<endl;
  v.pop_back();
  v.pop_front();
  v.print();
  cout<<"size: "<<v.size()<<endl;
  cout<<"capacity: "<<v.capacity()<<endl;
   cout<<"Insert 99 at index 2"<<endl;
   v.insert(99,2);
   v.print();*/


return 0;


}