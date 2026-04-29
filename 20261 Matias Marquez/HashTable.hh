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
        HashNode* next; //para colisiones
    public:
        HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
        const K& getKey() const { return key; }
        const V& getValue() const { return value; }
        void setValue(const V& v) { value = v; }
        HashNode* getNext() const { return next; }
        void setNext(HashNode* n) { next = n; }
    };
    Vector<HashNode*> table(10);
    unsigned int sz;
public:
    HashTable() : sz(0) {
        for (unsigned int i = 0; i < table.capacity(); ++i) {
            table[i] = nullptr;
        }
    }

 ~HashTable() {
        for (unsigned int i = 0; i < table.capacity(); ++i) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* toDelete = current;
                current = current->getNext();
                delete toDelete;
            }
            table[i] = nullptr;
        }
    }

    unsigned int hashFunction(const K& key) const {
        unsigned int hash = 0;
        for (unsigned int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % 10;    }
        return hash;}
    

    void insert(const K& key, const V& value) {
        HashNode* newNode = new HashNode(key, value);
        unsigned int index = hashFunction(key);
        if (table[index] == nullptr) {
             table[index] = newNode;
        }else 
        {
        HashNode* current = table[index];
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
        }
    }

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
        }
    }
};

#endif 