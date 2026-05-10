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
        Node* parent;
        Node* left;
        Node* right; 
    public:
        Node():key(),val(),Color(RED),parent(nullptr),left(nullptr),right(nullptr){}
        Node(K a, V b):key(a),val(b),Color(RED),parent(nullptr),left(nullptr),right(nullptr){}
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
        void setparent(Node* p) {parent = p;}
        Node* getparent() const {return parent;}
        void setcolor(Color c) {color = c;}
        Color color() const {return color;}
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

    Color getcolor(Node* n){
        if (n) return n->color();
        return BLACK;
    }

    void insert(const K& key, const V& val){
        Node* newnode = new Node(key, val);
        bool wasinserted = false;
        root = insert(newnode, root, &wasinserted);
        if(wasinserted)
        fixinsert(newnode);
        else 
        delete newnode;
    }

    void remove(const K& key){
        bool needfixup = false;
        Node* x =  nullptr;
        Node* xparent = nullptr;
        root = remove(key, root, &needfixup, &x, &xparent);
        if(needfixup)
            removefixup(x, xparent);
    }

    private:

    Node* remove(K& key, Node* n, bool& needfixup, Node*& x, Node*& xparent){
        if (n) return n;
        if (key < n->getkey()){
            Node* leftchild = remove(key, n->getleft(), &needfixup, &x, &xparent);
            n->setleft(leftchild);
            if (leftchild) leftchild->setparent(n);
            return n;
        } else if (n->getkey() < key){
            Node* rightchild = remove(key, n->getright(),&needfixup, &x, &xparent);
            n->setright(rightchild);
            if (rightchild) rightchild->setparent(n);
            return n;
        } else {
            if (!n->hasleft() && !n->hasleft()){
                if (n->color()== BLACK) needfixup = true;
                x = nullptr;
                xparent = n->getparent;
                delete n;
                sz--;
                return nullptr;
            } else if (!n->hasleft()){
                if (n->color()== BLACK) needfixup = true;
                x = n->getright();
                xparent = n->getparent();
                delete n;
                sz --;
                return x;
            }else if (!n->hasright()){
                if (n->color()==BLACK) needfixup = true;
                x = n->getleft();
                xparent = n->getparent();
                delete n;
                sz--;
                return x;
            }else {
                Node* m = findmin(n->getright());
                n->setkey(m->getkey());
                n->setval(m->getvalue());

                Node* rightchild = remove(m->getkey(), n->getright(), &needfixup, &x, &xparent);
                n->setright(rightchild);
                if (rightchild) rightchild->setparent(n);
                return n;
            }
        }
    }


    void removefixup(Node* x, Node* xparent){
        if (root == x || getcolor(x) == RED){
            if (x) x->setcolor(RED);
        return;}
        if (x == xparent->getleft()){
            Node* w = xparent->getright();
            if (getcolor(w) == RED){
                w->setcolor(BLACK);
                xparent->setcolor(RED);
                leftrotate(xparent);
                removefixup(x,xparent);
                return;
            } else if (getcolor(w->getleft()) == BLACK && getcolor(w->getright())==BLACK){
                w->setcolor(RED);
               removefixup(xparent, xparent->getparent());
               return;
            } else {
                if (getcolor(w->getleft()) == RED){
                    w->setcolor(RED);
                    w->getleft()->setcolor(BLACK);
                    rightrotate(w);
                }else{
                    w->setcolor(getcolor(w->getparent));
                    xparent->setcolor(BLACK);
                    w->getright()->setcolor(BLACK);
                    leftrotate(xparent);
                    return;
                }    
            }}
        else {
        Node* w = xparent->getleft();
        if (getColor(w) == RED) {
            w->setcolor(BLACK);
            xparent->setcolor(RED);
            rightrotate(x_parent);
            removeFixup(x, x_parent);
            return;
        }

        if (getColor(w->getleft()) == BLACK && getColor(w->getright()) == BLACK) {
            w->setcolor(RED);
            removeFixup(xparent, xparent->getparent()); 
            return;
        } 
        else {
            if (getColor(w->getleft()) == BLACK) {
                if (w->getright() != nullptr) w->getright()->setcolor(BLACK);
                w->setcolor(RED);
                leftrotate(w);
                removeFixup(x, x_parent);
                return;
            }
            w->setcolor(getColor(x_parent));
            xparent->setcolor(BLACK);
            if (w->getleft() != nullptr) w->getleft()->setcolor(BLACK);
            rightrotate(x_parent);
            return; 
        }
    }
 }
 
    Node* insert(Node* newnode, Node* n, bool& wasinserted){
        if (n==nullptr){
            newnode->setparent(nullptr);
            wasinserted = true;
            return newnode;
        }
        if (newnode->getkey()< n->getkey())
            {n->setleft(insert(newnode, n->getleft(), wasinserted));
            n->getleft()->setparent(n);}
        else if (n->getkey()<newnode->getkey())
            {n->setright(insert(newnode, n->getright(), wasinserted));
            n->getright()->setparent(n);}
        else {
        n->setval(newnode->getvalue());
        wasinserted=false;}
        return n;
    }

    void fixinsert(Node* n){
        if(root==n)
            { n->setcolor(BLACK); return;}
        if(n->getparent()->color() == BLACK )   
            return;
        Node* parent = n->getparent();
        Node* grandpa = n->getparent()->getparent();
        Node* uncle = nullptr; 
        if(parent == grandpa->getright())
            uncle = grandpa->getleft();
        else 
            uncle = grandpa->getright();
        if (uncle != nullptr && uncle->color() == RED){
            grandpa->setcolor(RED);
            parent->setcolor(BLACK);
            uncle->setcolor(BLACK);
            fixinsert(grandpa);
            return;}
        if (parent == grandpa->getleft()){
            if(parent->getright()==n){
                leftrotate(parent);
                n = parent;
                parent = n->getparent();
            } parent->setcolor(BLACK);
              grandpa->setcolor(RED);
              rightrotate(grandpa);
        }else {
            if(parent->getleft()==n){
                rightrotate(parent);
                n = parent;
                parent = n->getparent();
            } parent->setcolor(BLACK);
              grandpa->setcolor(RED);
              leftrotate(grandpa);
        } root->setcolor(BLACK);
    }

    void rightrotate(Node* n){
        Node* newchild = n->getleft()->getright();
        Node* newparent = n->getleft();
        n->setleft(newchild);
        if (newchild != nullptr)
            newchild->setparent(n);
        Node* oldparent = n->getparent();
        newparent->setparent(oldparent);
        newparent->setright(n);
        if (oldparent == nullptr){
            root = newparent;
        }else{
        if(n==oldparent->getleft())
        {   oldparent->setleft(newparent);}
        else{
            oldparent->setright(newparent);
        }}
         n->setparent(newparent);
    }

    void leftrotate(Node* n){
        Node* newchild = n->getright()->getleft();
        Node* newparent = n->getright();
        n->setright(newchild);
        if (newchild != nullptr)
            newchild->setparent(n);
        Node* oldparent = n->getparent();
        newparent->setparent(oldparent);
        newparent->setleft(n);
        if (oldparent == nullptr){
            root = newparent;
        }else{
        if(n==oldparent->getleft())
        {   oldparent->setleft(newparent);}
        else{
            oldparent->setright(newparent);
        }}
         n->setparent(newparent);
    }

    Node* findmin(Node* n){
        if(n->hasleft())
          {n = n->getleft();
           return(findmin(n)); }
        else 
         return n;
    }

  
};


#endif 