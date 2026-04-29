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
            delete table[i]; //eliminar colisiones falta implementar
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

    bool find(const K& key) const {
        unsigned int index = hashFunction(key);
        if (table[index] != nullptr && table[index]->key == key) {
            return true;
        }
        return false;
    }

    void remove(const K& key) {
        unsigned int index = hashFunction(key);
        if (table[index] != nullptr && table[index]->key == key) {
            delete table[index];
            table[index] = nullptr;
        }
    }
};

#endif 