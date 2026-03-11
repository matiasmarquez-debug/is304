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
list.push_back(1);list.push_back(2);list.push_back(2);list.push_back(1);list.push_back(1);
list.push_back(2);
list.print();
list.remove_all(1);
list.print();
return 0;
}