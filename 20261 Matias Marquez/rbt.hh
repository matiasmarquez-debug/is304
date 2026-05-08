#ifndef _RBT_HH_
#define _RBT_HH_
#include <iostream>
using namespace std;
enum Color { RED, BLACK };

template<typename K, typename V>
class RBT {
private:
    class Node{
    private:
        K key;
        V val;
        Color color;
        Node* left;
        Node* right; 
    public:
        Node():key(),val(),Color(RED),left(nullptr),right(nullptr){}
        Node(K a, V b):key(a),val(b),Color(RED),left(nullptr),right(nullptr){}
        const K& getkey() const { return key; }
        const V& getvalue() const {return val;}
        V& getvalue() {return val;}
        void setval(const V& v) {val = v;}
        void setkey(const &K k) {key=k;}
        bool hasleft() {return left != nullptr;}
        bool hasright() {return right != nullptr;}
        Node* getleft() const{return left;}
        Node* getright() const{return right;}
        void setleft(Node* l) {left = l;}
        void setright(Node* r) {right = r;}
    };
Node* root;
unsigned int sz;
public:
    RBT(): rooot(nullptr), sz(0){}
    ~RBT(){clear();}
    unsigned int size() const {return sz;}
    bool empty() const {return root==nullptr;}

    void clear(Node* n){
        if (n==nullptr) return;
        clear(n->getleft());
        clear(n->getright());
        delete n;
    }

    private:
    Node* insert(const K& key, const V& val, Node* n){
        if (n==nullptr){
            Node* p = new Node(key,val);
            sz++;
            return p;}
        if (key < n->getkey())
            n->setleft(insert(key,val,n->getleft()));
        if (n->getkey()<key)
            n->setright(insert(key,val,n->getright()));
        else 
            n->setval(val);
        return n;
    }

  
};


#endif 