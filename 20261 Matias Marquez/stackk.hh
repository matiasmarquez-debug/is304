#ifndef _STACKK_HH_
#define _STACKK_HH_
#include "Slist.hh"
#include <iostream>
#include <cassert>

template <typename T>
class Stack {
private:
List<T> storage;
public:
Stack():storage(){}
Stack(const Stack<T>& other) : storage(other.storage){}
bool empty() const {  return storage.empty(); }
unsigned int size() const {return storage.size();}
void push(const T& elem) {
    storage.push_back(elem);
}
void pop() {
    assert(!empty());
    storage.pop_back();
}



};


#endif