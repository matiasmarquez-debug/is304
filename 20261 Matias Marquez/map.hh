#ifndef _MAP_HH_
#define _MAP_HH_
#include <iostream>
#include <stdexcept>
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
        void setkey(const K& k) {key = k;}
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
    ~Map(){clear();}

    Map(const Map& m) {
        root = copy(m.root);
        sz = m.size();
    }
    Map& operator=(const Map& other){
        if(this==&other) return *this;
        clear();
        root = copy(other.root);
        sz = other.size();

        return *this;
    }
   
    unsigned int size() const {return sz;}
    bool empty() const {return root==nullptr;}
    void insert(const K& key, const V& val){
    root = insert(key,val,root);
    }
    void clear(){
    clear(root);
    root = nullptr;
    sz = 0;
    }
    void print(){
    print(root);
    cout<<""<<endl;
    }  
  
    void remove(const K& key){
    root = remove(key, root);
    }
   /*const V* search(const K& key) const {
        Node* n = search(key,root);
        V* p = nullptr;
        if (n!=nullptr)
            p = &(n->getval());
        return p;  
    }*/ 

    const V& search(const K& key) const {
    const Node* n = search(key, root);
    if (n == nullptr)
        throw std::out_of_range("clave no encontrada");
    return n->getval();
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

    void print(Node* n){
    if (n==nullptr) return;
    print(n->getleft());
    cout << n->getkey() << " :" << n->getval() << endl;
    print(n->getright());
    }

    void clear(Node* n){
    if (n==nullptr) return;
    clear(n->getleft());
    clear(n->getright());
    delete n;}

    Node* remove(const K& key, Node* n){
    if (n==nullptr) return n;
    if (key < n->getkey())
        {n->setleft(remove(key,n->getleft())); return n;}
    else if(n->getkey()<key)
        {n->setright(remove(key,n->getright())); return n;}
    else{
        if (!n->hasleft() && !n->hasright()){
            delete n;
            sz--;
            return nullptr;}
        else if(!n->hasleft()){
            Node* p= n->getright();
            delete n;
            sz--;
            return p;}
        else if(!n->hasright()){
            Node* p= n->getleft();
            delete n;
            sz--;
            return p;}
        else{
            Node* m = findmin(n->getright());
            n->setval(m->getval());
            n->setkey(m->getkey());
            n->setright(remove(m->getkey(),n->getright()));
            return n;
            }
    }}

    Node* findmin(Node* n){
    if (!n->hasleft()) return n;
    return findmin(n->getleft());}

    const Node* search(const K& key,const Node* n) const{
       if (n==nullptr)
            return nullptr;
        else if (key<n->getkey())
            return search(key, n->getleft());
        else if (n->getkey()<key)
            return search(key, n->getright());
        else
            return n;
    }

    Node* copy(const Node* n){
    if (n == nullptr) return nullptr;
    Node* p = new Node(n->getkey(),n->getval());
    p->setleft(copy(n->getleft()));
    p->setright(copy(n->getright()));
    return p;
    }
};



#endif