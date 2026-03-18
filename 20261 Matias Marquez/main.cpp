#include "Vector.hh"
#include "LIST.hh"
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
int main() {
List<int> list;
list.push_back(3);list.push_back(4);list.push_back(7);   list.push_back(2);list.push_back(1);   list.push_back(9);list.push_back(6);   list.push_back(5);   list.push_back(8);   
list.print();
list.merge_sort();
list.print();
return 0;
}