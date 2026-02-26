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
        assert(!empty())
        for(int i = 0; i <= sz; i++)
           {storage[i]=storage[i+1];}
        sz--;
    }

    void remove(unsigned int pos){  
       assert(pos<sz);
         for(int i = pos ; i < sz; i++)
       {storage[i] = storage[i+1];}  
       sz--;
    }

     void erase(unsigned int from, unsigned int to) //[)
  { assert((from<to)&&(to<=sz));
      unsigned int newsz = sz-(to-from);
     for (int i = from; i < newsz; i++)
     {
         storage[i]=storage[to];
         to++;
     }
    sz=newsz;
  }

     void print() const {
        cout << "{";
        for(unsigned int i = 0; i < sz; i++) {
            cout << storage[i] << " ";
        }
        cout << "}" << endl;
    }

private:
    void resize() {
        if (sz == capacity) {
            // El arreglo esta lleno
            unsigned int newCapacity = capacity * 1.5 + 1;
            T* newStorage = new T[newCapacity];
            for(unsigned int i = 0; i < sz; i++) {
                newStorage[i] = storage[i];
            }
            delete [] storage;
            storage = newStorage;
            capacity = newCapacity;
        }
    }
};

int main() {

//Exercise 1.1 - Basicoperations
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
return 0;
}