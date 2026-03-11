#ifndef _LIST_HH_
#define _LIST_HH_
#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
class List {
private:
 class Node{
       private:
       T data;
        Node* next;
        public:
    Node(){
        data=T();
        next=nullptr;
    }
    Node (const T& elem){
        data=elem;
        next=nullptr;
    }
    void set_next(Node *n){
        next=n;
    }
    Node* get_next(){
        return next;
    }
    const T& get_data(){
        return data;
    }
    void set_data(const T& elem){
        data=elem;
    }
 };

 unsigned int sz;
 Node* first;
 Node* last;

public:
    List() {
        sz=0;
        first=nullptr;
        last=nullptr;
    }

    List(const List<T>& other) {
        sz=0;
        first=nullptr;
        last=nullptr;
    }

    ~List() { Node* current = first;
     clear();
    }

     void push_back(T elem) {
        Node* new_node = new Node(elem);
        if(empty()){
            first = new_node;
            last = new_node;
        } else {
            last->set_next(new_node);
            last = new_node;
        }
        new_node->set_next(nullptr);
        sz++;
    }

    unsigned int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    void print() const {
        if (empty()){
        cout<<"{}"<<endl; return;}
        Node* tmp = first;
        cout<<"{ ";
        for( unsigned int i =0; i<sz; i++)
        {cout<<tmp->get_data()<<" ";
        tmp= tmp->get_next();}
        cout<<"}"<<endl;
    }

    Node* at_node(unsigned int pos) const {
        assert(pos < sz);
        Node* tmp = first;
        for (unsigned int i = 0; i < pos; i++) {
            tmp = tmp->get_next();
        }
        return tmp;
    }

    void push_front(T elem) {
      Node* new_node = new Node(elem);
      if (empty())
      {first = new_node;
      last = new_node;}
      else 
        {new_node->set_next(first);
            first = new_node;}
            sz++;
    }

  void pop_front (){
    assert(!empty());
    Node* tmp;
    tmp = first->get_next();
    delete first;
    first=tmp;
    sz--;
    if (sz==0)
    {
        last=nullptr;
    }
  }
 
  void pop_back(){
  assert(!empty());
    Node* tmp=first;
    for (unsigned int i=0; i<sz-1; i++)
    tmp = tmp->get_next();
    delete last;
    last = tmp;
    last->set_next(nullptr);
   sz--;
  }

 void insert(const T& elem, unsigned int pos){
    assert(pos <= sz);
    if (pos == 0) {
        push_front(elem);
        return;
    }
    if (pos == sz) {
        push_back(elem);
        return;
    }
    Node* new_node = new Node(elem);
    Node* tmp=first;
    for(unsigned int i = 0; i<pos-1; i++)
    tmp = tmp->get_next();
    new_node->set_next(tmp->get_next());
    tmp->set_next(new_node);
    sz++;
 }

 void erase(unsigned int pos){
    assert(pos < sz);
    if (pos == 0) {
        pop_front();
        return;}
    if (pos == sz-1) {
        pop_back();
        return;}
    Node* tmp=first;
    Node* delet;
    for (unsigned int i =0; i < pos-1; i++)
    tmp = tmp->get_next();  
    delet= tmp->get_next();
    tmp->set_next(delet->get_next());
    delete delet;
    sz--;
 }

void erase(unsigned int from, unsigned int to){
    assert(from < to && to <= sz);
    Node* tmp=first;
    Node* delet=nullptr;
    Node* tmpa=nullptr;
    for (unsigned int i =0; i < from-1; i++)    
    tmp = tmp->get_next();
    tmpa= tmp->get_next();
    for (unsigned int i = from; i < to; i++)
    {delet=tmpa;
    tmpa= (tmpa->get_next());
    delete delet;
    }
    tmp->set_next(tmpa);
    if(from==0)
    {
        first = tmpa;
    }
    if(to==sz)
    {
        last = tmp;
    }
       sz=sz-(to-from);
 }
void clear(){ Node* current = first;
    while (current != nullptr) {
        Node* next = current->get_next();
        delete current;
        current = next;
    }
    first = nullptr;
    last = nullptr;
    sz = 0;
}
bool contains(const T& elem) const{
  Node* tmp=first;
  for(unsigned int i = 0; i<sz; i++)
  {
    if (elem==tmp->get_data())
    return true;
    tmp= tmp->get_next();
  }
  return false;
}
 
 const int find(const T& elem) const{
    Node* tmp=first;
    for (unsigned int i = 0; i<sz; i++)
    {
        if (tmp->get_data()==elem)
        return i;
        tmp = tmp->get_next();
    }
    return -1;
}

void remove(const T& elem){
    assert(!empty());
    int pos = find(elem);
    if (pos!=-1)
    erase(pos);
}
void replace(const T& oldval, const T& newval){
  int pos= find(oldval);
  if(pos != -1)
  at_node(pos)->set_data(newval);
}

void remove_all(const T& elem){ //corregir casos de first y last
    assert(!empty());
    while (!empty() && first->get_data()==elem){
        pop_front();
    } if (empty()) return;
    Node* tmp=first;
    Node* remove=nullptr;
    while (tmp->get_next()!=nullptr)    {
        if (tmp->get_next()->get_data()==elem)
        {
            remove=tmp->get_next();
            tmp->set_next(remove->get_next());
             if (remove == last)
                last = tmp;
            delete remove;
            sz--;
        }
        else
        tmp= tmp->get_next();}
}

void replace_all(const T& oldval, const T& newval){
    Node* tmp=first;
   while(tmp!=nullptr)
    {
        if (oldval==tmp->get_data())
        tmp->set_data(newval);
        tmp=tmp->get_next();
    }
}

unsigned int count(const T& elem) const{
    unsigned int count=0;
    Node* tmp=first;
    for (unsigned int i = 0; i<sz; i++)
    {
        if (tmp->get_data()==elem)
        count++;
        tmp = tmp->get_next();
    }
    return count;}

};



#endif