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
        Node* tmp = other.first;
        while (tmp!=nullptr)
        {push_back(tmp->get_data());
        tmp = tmp->get_next();}
    }

    ~List() {
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

 Node* at_node(unsigned int pos)  {
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
   if (sz==1)
   {delete first;
     first = nullptr; last=nullptr; sz--; return;}
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
    if (from == 0)
    {for (int i = 0; i<to; i++)
      pop_front();
       return;}
    Node* tmp = at_node(from);
    Node* tmpa = at_node(from-1);
    Node* borrar = nullptr;
    for(unsigned int i = from; i<to ; i++)
    { borrar = tmp;
        tmp = (tmp->get_next());
        delete borrar;
    }
   tmpa->set_next(tmp);
  if (to == sz)
    last = tmpa;

   sz = sz - (to-from);
   
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
  return indices_of(elem).size();}

List<int> indices_of(const T& elem) const{
    List<int> indices; 
    if (empty())
    return indices;
    Node* tmp=first;
    unsigned int i = 0;
    while(tmp!=nullptr)
    {
        if (elem==tmp->get_data())
        indices.push_back(i);
     tmp = tmp->get_next();
     i++;
    }
    return indices;
}

void swap(unsigned int i, unsigned int j){
    assert(i<sz && j<sz);
    if (i==j) return;
    Node* tmp1 = at_node(i);
    Node* tmp2 = at_node(j);
    T ayuda = tmp1->get_data();
    tmp1->set_data(tmp2->get_data());
    tmp2->set_data(ayuda);
}
void reverse(){
    reverse(0,sz-1);
}
void reverse(unsigned int i, unsigned int j){
    if (sz==0 || sz==1) return;
    while(i<j){
        swap(i,j);
        i++; j--;
    }
}

void rotate_left(unsigned int k){
    k=k%sz;
    if (sz ==0 || k==0) return;
    reverse(0,k-1);
    reverse(k, sz-1);
    reverse();
}

void rotate_right(unsigned int k){
      k=k%sz;
    if (sz ==0 || k==0) return;
    rotate_left(sz-k);
}

void merge_sort(){
    if( sz<= 1) return;
  List<T> left, right;
  split(left,right);
  left.merge_sort();
  right.merge_sort();
  *this = merge(left, right);
}
private: 
List<T> merge(List<T> left, List<T> right){
 List<T> newlist;
 Node* tmpl = left.first;
 Node* tmpr = right.first;
//unsigned int i =0, j=0;
unsigned int tam =left.size()+right.size();
while (newlist.size()<tam){
    if(tmpl==nullptr)
    {while (tmpr!=nullptr)
         {newlist.push_back(tmpr->get_data());
          tmpr=tmpr->get_next();
         //j++;
         } return newlist;
    } else if (tmpr==nullptr)
         {while (tmpl!=nullptr)
         {newlist.push_back(tmpl->get_data());
          tmpl=tmpl->get_next();
        //  i++;
         } return newlist;
    } 
    if (tmpl->get_data() < tmpr->get_data())
        {newlist.push_back(tmpl->get_data());
        tmpl = tmpl->get_next();
       //  i++;
       }
   else 
       {newlist.push_back(tmpr->get_data());
       tmpr = tmpr->get_next();
       //j++;
       }
   
   }
   return newlist;
}

void split(List<T>& left, List<T>& right){
  unsigned int mitad = sz/2;
 Node* tmp = first;
 for (int i = 0; i<mitad; i++)
 {left.push_back(tmp->get_data());
  tmp = tmp->get_next();}
  tmp = at_node(mitad);
 for (int i = mitad; i<sz; i++)
 {right.push_back(tmp->get_data());
tmp = tmp->get_next();}}


public:
void operator=(const List<T>& other)
{  if( this == &other) return;
    clear();
    Node* tmp = other.first;
    while (tmp!=nullptr)
      {push_back(tmp->get_data());
        tmp = tmp->get_next();}
}

void append(const List<T>& other) {
     if (other.empty()) return;
    unsigned int tam = other.size();
    Node* tmp=other.first;
    for(unsigned int i=0; i<tam; i++)
    {push_back(tmp->get_data());
    tmp = tmp->get_next();
    }
    }
List<T> slice(unsigned int from, unsigned int to) const {
    assert(from<=to&&to<=sz);
    List<T> newl;
    Node* tmp = at_node(from);
    while (from<to){
       newl.push_back(tmp->get_data());
       tmp= tmp->get_next();
        from++;
    }
   return newl;
}

template<typename Predicate>
bool any (Predicate p) const {
    Node* tmp=first;
    while ( tmp != nullptr){
     if(p(tmp->get_data()))
     return true;

     tmp = tmp->get_next();
    }return false;
}

template<typename Predicate>
 bool all(Predicate p) const {
    if (empty()) return true;
    Node* tmp=first;
    while ( tmp != nullptr){
     if(!p(tmp->get_data()))
     return false;

     tmp = tmp->get_next();
    }return true;
}
template<typename Predicate>
bool none(Predicate p) const {
return !any(p);
}

template<typename Predicate>
List<T> filter(Predicate p) const {
    List<T> filtro;
    Node* tmp = first;
    while (tmp!= nullptr)
    {
        if (p(tmp->get_data()))
        filtro.push_back(tmp->get_data());

    tmp = tmp->get_next();
    } return filtro;
}

template<typename Function>
auto map(Function f) const -> List<decltype(f(std::declval<T>()))>
{
using R = decltype(f(std::declval<T>()));
List<R> result;
Node* tmp = first;
while (tmp != nullptr){
    R f_tmp = f(tmp->get_data());
    result.push_back(f_tmp);
    tmp = tmp->get_next();
}return result;
}

template<typename Function>
void for_each(Function f)  {
    Node* tmp = first;
    while (tmp!= nullptr)
    {
    tmp->set_data(f(tmp->get_data()));   
    tmp = tmp->get_next();
    } 
}

template<typename Function>
T foldl(Function f, T acum) const { 
    Node* tmp = first;
    while (tmp != nullptr) {
        acum = f(acum, tmp->get_data());
        tmp = tmp->get_next();
    }
    return acum;
}
template<typename Function>
T foldr(Function f, T acum) const{
    List<T> reversed(*this);
    reversed.reverse();
    return reversed.foldl(f, acum);
}
};




#endif