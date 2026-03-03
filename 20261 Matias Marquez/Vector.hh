#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
class Vector {
private:
    T* storage;
    unsigned int sz;
    unsigned int cap;
public:
    Vector() {
        cap = 5;
        storage = new T[cap];
        sz = 0;
    }

    Vector(unsigned int c){
       cap = c;
       storage = new T[cap];
       sz = 0;
    }

    ~Vector() {
        delete [] storage;
    }

    unsigned int size() const{
        return sz;
    }

    bool empty() const{
        return sz == 0;
    }
    
    unsigned int capacity() const {
        return cap;
    }

    void push_back(T elem) {
        resize();
        storage[sz] = elem;
        sz++;
    }

    void pop_back() {
        assert(!empty());
        sz--;
    }

    void pop_front(){
        assert(!empty());
        for(int i = 0; i <= sz-1; i++)
           {storage[i]=storage[i+1];}
        sz--;
    }

    void insert(const T& elem, unsigned int pos){
        assert(pos >= 0 && pos <= sz);
        resize();
        for(unsigned int i = sz;  i > pos; i--){
            storage[i] = storage[i-1];
        }
        storage[pos]= elem;
        sz++;
    }
 const T& front() const {
        assert(!empty());
        return storage[0];
    }

    T& front() {
        assert(!empty());
        return storage[0];
    }

    const T& back() const {
        assert(!empty());
        return storage[sz-1];
    }
  
    T& back() {
        assert(!empty());
        return storage[sz-1];
    }

    const T& at(unsigned int pos) const {
        assert(pos < sz);
        return storage[pos];
    }

    T& at(unsigned int pos) {
        assert(pos < sz);
        return storage[pos];
    }
    const T& operator[](unsigned int pos) const {
        return storage[pos];
    }

    T& operator[](unsigned int pos) {
        return storage[pos];
    }

    Vector(const Vector<T>& other) {
        cap = other.cap;
         sz = other.sz;
        storage = new T[cap];
        for (unsigned int i = 0; i < sz; i++) {
        storage[i] = other.storage[i];
    }
}
    void erase(unsigned int pos){  
       assert(pos<sz);
         for(int i = pos ; i < sz; i++)
       {storage[i] = storage[i+1];}  
       sz--;
    }

     void erase(unsigned int from, unsigned int to) //[)
  { assert((from<to)&&(to<=sz));
      unsigned int newsz = sz-(to-from);
     for (unsigned int i = from; i < newsz; i++)
     {
         storage[i]=storage[to];
         to++;
     }
    sz=newsz;
  }
 void clear(){
    sz=0;
 }

 bool contains(const T& elem) const{
    if (find(elem)!=-1)
    return true;
    return false;
 }
 int find(const T& elem) const {
    for (unsigned int i = 0; i< sz; i++)
    {if (elem == storage[i])
    return i;}
    return -1;
 }

  void remove(const T& elem){
        for (unsigned int i=0; i < sz; i++)
        {
            if(elem == storage[i]){
            erase(i);
            return;
        }}
    }
void replace(const T& oldval, const T& newval){
  for(unsigned int i=0; i < sz; i++){
    if (storage[i]==oldval){
        storage[i]=newval;
        return;}
    
    }
  }
void remove_all(const T& elem){
    for (unsigned int i=0;i<sz; i++)
    {
            if(elem == storage[i]){
            erase(i);
        }}
}
void replace_all(const T& oldval, const T& newval){
  for(unsigned int i=0; i < sz; i++){
    if (storage[i]==oldval){
        storage[i]=newval;
        ;}
    
    }
  }
unsigned int count(const T& elem) const{
return indices_of(elem).size();
}

Vector<int> indices_of(const T& elem)const{
   Vector<int> indicesof;
   for(unsigned int i=0; i<sz; i++)
   if (storage[i]==elem)
   indicesof.push_back(i);
return indicesof;
}

void swap(unsigned int i,unsigned int j){
if (i==j||i>=sz||j>=sz)
return;
  T keep=storage[j];
  at(j) = storage[i];
  at(i) = keep;
}
void reverse(){
    unsigned int nsz = sz-1;
    for (unsigned int i =0; i<nsz; i++){
    swap(i,nsz);
    nsz--;}
}

void rotate_left(unsigned int k){
    if ((sz==0)||((k%sz)==0))
    return;
    unsigned int kn = k-1;
    unsigned int endpos = sz -1;
    for(unsigned int i=0; i<kn; i++)
    {
        swap(i,kn);
        kn--;
    }
    for(unsigned int i=k; i<endpos; i++)
    {
        swap(i,endpos);
        endpos--;
    }
     reverse();
}

void rotate_right(unsigned int k){
 if ((sz==0)||((k%sz)==0))
    return;
    unsigned int kn = k;
    unsigned int endpos = sz-1;
    for(unsigned int i=0; i<kn; i++)
    {
        swap(i,kn);
        kn--;
    }
    for(unsigned int i=k+1; i<endpos; i++)
    {
        swap(i,endpos);
        endpos--;
    }
     reverse();
}

void sort(){
    if (sz<=1)return;
  quicksort(0,sz-1);
}
void quicksort(int front, int end){
    int i = front - 1;
    int pivot = storage[end];
    if (front>=end)
    return;
    else{
     for( int j = front; j < end; j++)
     {
        if (storage[j]>pivot)
        continue;
        else if (storage[j]<=pivot)
        {
            i++;
            swap(i,j);
        }
     }
     swap(i+1,end);
     quicksort(front,i);
     quicksort(i+2,end);
    }
}
 void append(const Vector<T> &other){
    if (other.empty())
    return;
    for(unsigned int i=0; i<other.size(); i++)
    push_back(other.operator[](i));
    sort(); 
 }

 Vector<T> slice(unsigned int from, unsigned int to)
{ assert(from<to||to<=sz);
   Vector<T> vectorslice;
   for ( unsigned int i=from; i<to; i++)
   vectorslice.push_back(storage[i]);
   return vectorslice;
}

Vector& operator=(const Vector<T> &other)
{if (this == &other) return *this; 
    
    delete[] storage;  
    
    cap = other.cap;
    sz = other.sz;
    storage = new T[cap];
    for (unsigned int i = 0; i < sz; i++) {
        storage[i] = other.storage[i];
    }
    
    return *this;
}
template<typename P>
bool any(P predicate) const {
    for (unsigned int i = 0; i < sz; i++) {
        if (predicate(storage[i]))
            return true;
    }
    return false;
}

     void print() const {
        cout << "{ ";
        for(unsigned int i = 0; i < sz; i++) {
            cout << storage[i] << " ";
        }
        cout << "}" << endl;
    }

private:
    void resize() {
        if (sz == cap) {
            // El arreglo esta lleno
            unsigned int newCapacity = cap * 1.5 + 1;
            T* newStorage = new T[newCapacity];
            for(unsigned int i = 0; i < sz; i++) {
                newStorage[i] = storage[i];
            }
            delete [] storage;
            storage = newStorage;
            cap = newCapacity;
        }
    }
};

