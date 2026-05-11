#include <iostream>
#include "Vector.hh"
#include <string>
using namespace std;

template <typename K, typename V>
class HashTable {
private:
    Vector<pair<K, V>> table;
    unsigned int m;;
    unsigned int sz;
public:
    unsigned int hashFunction(const K& key) const {
    unsigned int hash = 0;  
    for (unsigned int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % m;    }
        return hash;}

    HashTable(unsigned int capacity) : sz(0), m(capacity) {
        table.resize(capacity);
        for (unsigned int i = 0; i < m; i++) {
            table[i] = make_pair("", V());
        }
    }

    void insert(const K& key, const V& value) {
        unsigned int i = hashFunction(key);
        unsigned int firstindex = i;
        for (i; i < table.capacity(); i++) {
            if (table[i].first == key) {
                table[i].second = value;
                return;
            }else if (table[i].first == "") {
                table[i] = make_pair(key, value);
                  sz++;
                return;
            }
        }
        for (i=0; i<firstindex; i++){
             if (table[i].first == key) {
                table[i].second = value;
                return;
            }else if (table[i].first == "") {
                table[i] = make_pair(key, value);
                sz++;
                return;
            }
        }
        rehash();
        insert(const K& key, const V& val);
  }
  void limpiarinicio(){
    for (unsigned int i = 0; i< table.capacity(); i++){
        table[i] = make_pair("",V());
        sz = 0;
    }
  }

  void rehash()
    {m = table.capacity() * 1.5;
    vector<pair<K,V>> copy(&table);
    limpiarinicio(table);
    table.resize(m);
    for (unsigned int i = 0; i < copy.size(); i++){
        if (copy[i].first != "")
        insert(copy[i].first, copy[i].second);
     }
    }  
    
    };