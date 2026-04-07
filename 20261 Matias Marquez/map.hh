#ifndef _MAP_HH_
#define _MAP_HH_
#include <iostream>
using namespace std;

template<typename K, typename V>
class Map {
private:
    class Node {
    private:
        K key;
        V val;
        Node* left;
        Node* right;
    public:
        Node():key(),val(),left(nullptr),right(){}
        Node(K a, V b):key(a),val(b),left(nullptr),right(){}
        bool hasleft() {return left != nullptr;}
        bool hasright() {return right != nullptr;}
        const K& getkey() const{return key;}
        const V& getval() const{return val;}
        void setval(const V& v) {val = v;}
        Node* getleft() const{return left;}
        Node* getright() const{return right;}
        void setleft(Node* l) {left = l;}
        void setright(Node* r) {right = r;}
    };
Node* root;
unsigned int sz;
public:
    Map(): root(nullptr), sz(0){}
    unsigned int size(){return sz;}
    bool empty(){return root==nullptr;}
    void insert(const K& key, const V& val){
    root = insert(key,val,root);
    }
private:
    Node* insert(const K& key, const V& val, Node* n){
    if (n==nullptr){
        Node *p = new Node( key, val);
        sz++;
        return p;
    }
    if (key < n->getkey())
      n->setleft(insert(key,val,n->getleft()));
    else if (n->getkey()<key)
      n->setright(insert(key,val,n->getright()));
    else 
    n->setval(val);
    return n;
    }
};



#endif