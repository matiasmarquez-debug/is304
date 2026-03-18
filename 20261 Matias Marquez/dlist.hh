#ifndef _DLIST_HH_
#define _DLIST_HH_
#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
class Dlist {
 private:
         class Node{
            private:
             Node* next;
             Node* prev;
             T data;
            public:
             Node(){data=T(); next=nullptr; prev=nullptr;}
             Node(const T& elem){data=elem; next=nullptr; prev=nullptr;}
             void set_next(Node* nodo){ next = nodo; }
             void set_prev(Node* nodo){ prev=nodo;}
             void set_data(const T& elem){ data = elem;}
             Node* get_next() const { return next;}
             Node* get_prev() const {return prev;}
             const T& get_data() const{return data;}                 };
 unsigned int sz;
 Node* first; Node* last;
public:
 Dlist(){first=nullptr; last=nullptr; sz=0;}

 void push_back(const T& elem){
    Node* nodo = new Node(elem);
    if(sz==0)
    {first = nodo; last = nodo; }
    else  
    {last->set_next(nodo);
    nodo->set_prev(last);
    last = nodo;} sz++;
 } 
};
#endif