#ifndef _HASHTABLE_HH_
#define _HASHTABLE_HH_
#include <iostream>
#include "LIST.hh"
#include "Vector.hh"
#include <string>

template <typename K, typename V>
class HashTable {
private:
  class HashNode {
    private:
        K key;
        V value;
    public:
        HashNode(K k, V v) : key(k), value(v) {}
        const K& getKey() const { return key; }
        const V& getValue() const { return value; }
        void setValue(const V& v) { value = v; }
    };
    Vector<List<HashNode>> table(10);
    unsigned int sz;
public:
    HashTable() : sz(0) {
        for (unsigned int i = 0; i < table.capacity(); ++i) {
            table[i] = List<HashNode>();
        }
    }

 ~HashTable() {
        for (unsigned int i = 0; i < table.capacity(); ++i) {
<<<<<<< HEAD
            table[i].clear();
=======
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* toDelete = current;
                current = current->getNext();
                delete toDelete;
            }
            table[i] = nullptr;
>>>>>>> a4360fa23a62570254911599dbe24443b5dad72e
        }
    }

    unsigned int hashFunction(const K& key) const {
        unsigned int hash = 0;
        for (unsigned int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % 10;    }
        return hash;}
    

     void insert(const K& key, const V& value) {
        //HashNode* newNode = new HashNode(key, value);
        unsigned int index = hashFunction(key);
             table[index].push_back(HashNode(key, value));
        sz++;
    }

<<<<<<< HEAD
    std::pair<bool, V> find(const K& key) const {
    unsigned int index = hashFunction(key);
    auto* current = table[index].get_first();
    while(current != nullptr)
    {if(key==current->get_data().getKey())
        return std::make_pair(true, current->get_data().getValue());
    current = current->get_next();
    }

    return std::make_pair(false, V()); // No encontrado
}
    

    void remove(const K& key) {
    unsigned int index = hashFunction(key);
    
    auto* current = table[index].get_first(); // 'auto' deduce el tipo privado
    auto* prev = nullptr;                  // Inicializamos prev igual a current o nullptr
    
    while (current != nullptr) {
        if (current->get_data().getKey() == key) {
            if (prev == nullptr) {
                table[index].set_first(current->get_next());
            } else {
                prev->set_next(current->get_next());
            }
            delete current;
            sz--;
            return;
=======
    V find(const K& key) const {
        unsigned int index = hashFunction(key);
        HashNode* current = table[index];

        while (current != nullptr) {
            if (current->getKey() == key) {
                return current->getValue();
            }
            current = current->getNext();
        }

        throw std::runtime_error("Key not found");
    }

  void remove(const K& key) {
        unsigned int index = hashFunction(key);
        HashNode* current = table[index];
        HashNode* prev = nullptr;

        while (current != nullptr) {
            if (current->getKey() == key) {
                if (prev == nullptr) {
                    // El nodo a eliminar es el primero de la lista
                    table[index] = current->getNext();
                } else {
                    // El nodo está en medio o al final
                    prev->setNext(current->getNext());
                }
                delete current;
                sz--;
                return;
            }
            prev = current;
            current = current->getNext();
>>>>>>> a4360fa23a62570254911599dbe24443b5dad72e
        }
        prev = current;
        current = current->get_next();
    } 
  }
};

#endif 