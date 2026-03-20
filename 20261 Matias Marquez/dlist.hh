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
 Dlist(const Dlist<T>& other){
   first=nullptr; last=nullptr; sz=0;
   Node* tmp = other.first;
   while (tmp != nullptr){
      push_back(tmp->get_data());
      tmp = tmp->get_next();
   }}
  ~Dlist(){clear();}
  const unsigned int size() const { return sz;}
  bool empty(){return sz==0;}
   
  void clear(){
   if (empty()) return;
   Node* tmp = first;
   Node* borrar=nullptr;
   while( tmp!= nullptr ){
    borrar=tmp;
    tmp=tmp->get_next();
    delete borrar; 
   }first = nullptr; last = nullptr; sz=0;}

    void push_back(const T& elem){
    Node* nodo = new Node(elem);
    if(sz==0)
    {first = nodo; }
    else  
    {last->set_next(nodo);
    nodo->set_prev(last); }
    last = nodo; sz++;}

    void push_front(const T& elem){
      Node* nuevo = new Node(elem);
      if (sz==0) last=nuevo; 
      else 
      {nuevo->set_next(first);
      first->set_prev(nuevo);}
      first = nuevo;
      sz++;
    }
void pop_back(){
   assert(!empty());
   Node* borrar = last;
   last = last->get_prev();
   delete borrar;
   sz--;
   if (last==nullptr){ first = nullptr;}
   else if (sz==1) {last->set_next(nullptr);}
}

void pop_front(){
  assert(!empty());
   Node* borrar = first;
   first = first->get_next();
   delete borrar;
   sz--;
   if (first==nullptr){ last = nullptr;}
   else if (sz==1){first->set_prev(nullptr);}
}

void print(){
   Node* tmp = first;
   cout<<"{ ";
   while(tmp!=nullptr){
      cout<<tmp->get_data()<<" ";
      tmp = tmp->get_next();
   } cout<<"}"<<endl;
}
const Node* at(unsigned int pos) const {
   assert(pos<sz);
   Node* tmp = nullptr;
   if (pos < sz/2){tmp = first;
     for(unsigned int i= 0; i<pos; i++)
       tmp = tmp->get_next();
   } else {
      tmp=last;
      for(unsigned int i = sz-1; i>pos; i--)
      tmp = tmp->get_prev();
   } return tmp;
}
Node* at(unsigned int pos) {
  if (pos>=sz) return nullptr;
   Node* tmp = nullptr;
   if (pos < sz/2){tmp = first;
     for(unsigned int i= 0; i<pos; i++)
       tmp = tmp->get_next();
   } else {
      tmp=last;
      for(unsigned int i = sz-1; i>pos; i--)
      tmp = tmp->get_prev();
   } return tmp;
}

void erase(unsigned int pos){
   assert(pos<sz);
    if (pos==0){pop_front();}
   else if (pos==sz-1){pop_back();}
   else{Node* borrar = at(pos);
        Node* next = borrar->get_next();
        Node* prev = borrar->get_prev();
        next->set_prev(prev);
        prev->set_next(next);
     delete borrar;sz--;}
}
void swap(unsigned int i, unsigned int j){
  if (i>=sz && j>=sz) return;
    if (i==j) return;
    Node* tmp1 = at(i);
    Node* tmp2 = at(j);
    T ayuda = tmp1->get_data();
    tmp1->set_data(tmp2->get_data());
    tmp2->set_data(ayuda);}
 void reverse(){
   reverse(0,sz-1);
 }
void reverse(unsigned int i, unsigned int j){
      if (sz<=1) return;
      while(i<j)
      {
         swap(i,j);
         j--;
      }}

void swapdata (Node* tmp1, Node* tmp2)
{
   T x = tmp1->get_data();
   tmp1->set_data(tmp2->get_data());
   tmp2->set_data(x);
}

void quicksort(){quicksort(first,last);}
void quicksort(Node* low, Node* high){
   if(low==high|| low == nullptr || high == nullptr || low==high->get_next() )return;
    Node* piv = partition(low,high);
      quicksort(low, piv->get_prev());
      quicksort(piv->get_next(), high);
}
Node* partition (Node* low, Node* high){
   T pivot = high->get_data();
   Node* posp = low->get_prev();
   Node* recl = low;
   while(recl!=high){
      if(recl->get_data()<=pivot){
         if (posp==nullptr) posp = low; 
         else posp = posp->get_next();
         swapdata(posp, recl);
      } 
      recl=recl->get_next();
   }if (posp==nullptr)
   posp=low;
   else
   posp = posp->get_next();
   swapdata(posp, high);
   return posp;
}

void mergesort(){
   if (sz<=1) return;
   Dlist<T> left;
   Dlist<T> right;
   split(left,right);
   left.mergesort();
   right.mergesort();
   *this = merge(left,right);
}

private:

Dlist<T> merge(Dlist<T>& left, Dlist<T>& right){
   Dlist<T> newlist;
 Node* tmpl = left.first;
 Node* tmpr = right.first;
 while (tmpl!=nullptr || tmpr != nullptr)
 {
   if(tmpl == nullptr){
    while (tmpr!= nullptr){
      newlist.push_back(tmpr->get_data());
      tmpr = tmpr->get_next(); }}
   else if(tmpr == nullptr){
    while (tmpl!= nullptr){
      newlist.push_back(tmpl->get_data());
      tmpl = tmpl->get_next(); }}
   else{while( tmpl!=nullptr && tmpr != nullptr){
      if(tmpl->get_data()<tmpr->get_data())
      {newlist.push_back(tmpl->get_data());
        tmpl = tmpl->get_next();}else {
      newlist.push_back(tmpr->get_data());
       tmpr = tmpr->get_next();}
   }
   }
 }return newlist;
}

void split(Dlist<T>& left, Dlist<T>& right){
   Node* end = first;
   Node* mitad = first;
   while(end && end->get_next()){
      mitad = mitad->get_next();
      end = end->get_next()->get_next();
   }
   Node* tmp = first;
   while(tmp != mitad){
      left.push_back(tmp->get_data());
      tmp = tmp->get_next();
   }
      while(tmp != nullptr){
      right.push_back(tmp->get_data());
      tmp = tmp->get_next();
   }
}

public:
void append(const Dlist<T>& other){
   if(&other==this){
   Dlist<T> copia(other);
   append(copia);return;}
    Node* tmp = other.first;
   while (tmp != nullptr){
      push_back(tmp->get_data());
      tmp = tmp->get_next();
   }
}

void operator=(const Dlist<T>& other){
   if(this==&other) return;
   this->clear();
   Node* tmp = other.first;
   while (tmp!=nullptr){
      push_back(tmp->get_data());
      tmp = tmp->get_next();
   }
}

void unique(){
   Node* tmp = first;
   Node* borrar;
   Node* conecta;
   while(tmp && tmp->get_next())
   {   conecta = tmp->get_next();
      if (conecta && tmp->get_data()==conecta->get_data()){
        while(conecta && tmp->get_data() == conecta->get_data()){
         borrar = conecta;
         conecta = conecta->get_next();
         delete borrar;
        }
         tmp->set_next(conecta);
         if (conecta) {
    conecta->set_prev(tmp);
} else {
    last = tmp;
}
   } else tmp = tmp->get_next();
   
   }

}

void splice(Dlist<T>& other){
   if (this->empty())
   {
      first = other.first;
      last  = other.last;     
   } else 
   { other.first->set_prev(last);
   last->set_next(other.first);
    last=other.last;
   }
      other.first = nullptr;
      other.last = nullptr;
}


};
#endif