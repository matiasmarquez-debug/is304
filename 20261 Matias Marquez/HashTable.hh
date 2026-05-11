#ifndef _HASHTABLE_HH_
#define _HASHTABLE_HH_
#include <iostream>
#include "SLIST.hh"
#include "Vector.hh"
#include <string>
using namespace std;

template <typename K, typename V>
class HashTable {
private:
  /*class HashNode {
    private:
        K key;
        V value;
    public:
        HashNode(K k, V v) : key(k), value(v) {}
        const K& getKey() const { return key; }
        const V& getValue() const { return value; }
        void setValue(const V& v) { value = v; }
    };*/
    Vector<List<pair<K, V>>> table;
    unsigned int m;;
    unsigned int sz;
public:
    HashTable(unsigned int capacity) : sz(0), m(capacity) {
      table.resize(capacity);
    }

 ~HashTable() {
        for (unsigned int i = 0; i < table.capacity(); ++i) {
            table[i].clear();
        }
    }

    unsigned int hashFunction(const K& key) const {
        unsigned int hash = 0;
        for (unsigned int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % m;    }
        return hash;}
    
     void insert(const K& key, const V& value) {
        bool found = false; 
        unsigned int index = hashFunction(key);
        table[index].for_eachro([&](pair<K, V>& elem) {
            if (elem.first == key) {
                elem.second = value;
                found = true;
            }
        });
        if (found) return;
        table[index].push_back(make_pair(key, value));
        sz++;
    }

    pair<bool, V> find(const K& key) {
    unsigned int index = hashFunction(key);
    bool found = false;
    V val{};
    table[index].for_eachro([&](pair<K,V>& elem){
        if (elem.first==key)
            {found = true;
             val = elem.second;
            }
    }); return make_pair(found, val);
}
    

    void remove(const K& key) {
     unsigned int index = hashFunction(key);
     bool found = false;
     pair<K,V> lastelem=table[index].back();
     table[index].for_eachro([&](pair<K,V>& elem)
    {if(!found && elem.first==key){
        found = true;
        elem = lastelem;
    }
    });
    if (found == true) {
    table[index].pop_back();
    sz--;}
    }

    void rehash(unsigned int newcap){
        m = newcap;
        Vector<List<pair<K, V>>> copy(table);
        for (unsigned int i = 0; i < table.capacity(); ++i) {
            table[i].clear();
        } sz = 0;
        table.resize(m);
        for (unsigned int i = 0; i < copy.capacity(); ++i)
         copy[i].for_eachro([&](const pair<K,V>& elem){
            insert(elem.first,elem.second);
         });
    }

    
};

#endif 