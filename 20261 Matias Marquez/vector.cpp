#include <iostream>
#include <cassert>
using namespace std;

class Vector {
private:
    int* storage;
    unsigned int capacity;
    unsigned int sz;
public:
    Vector() {
        capacity = 5;
        storage = new int[capacity];
        sz = 0;
    }
    unsigned int size() {
        return sz;
    }
    void push_back(int elem) {
        resize();
        storage[sz] = elem;
        sz++;
    }
   bool empty() const {
        return sz == 0;
    }
    void remove(unsigned int pos){  
       assert(pos<sz);
         for(int i = pos ; i < sz; i++)
       {storage[i] = storage[i+1];}  
       sz--;
    }
     void erase(unsigned int from, unsigned int to) //[)
  { assert((from<sz)&&(to<=sz));
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
            unsigned int newCapacity = capacity * 1.5;
            int* newStorage = new int[newCapacity];
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
    Vector v;
    for(int i = 0; i < 11; i++) {
        v.push_back(i*10);
    }
    
    v.print();
    v.erase(4,11);
    cout<<"Aqui erase"<<endl;
    v.print();
    cout<<"Nuevo tamaño: "<<v.size()<<endl;
    v.remove(6);
    cout<<"Remove"<<endl;
    v.print();
    cout <<"sz: "<< v.size() << endl;
    return 0;  

}