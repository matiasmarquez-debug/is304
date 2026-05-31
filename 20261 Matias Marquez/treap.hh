#include <iostream>
#include <random>
#include <chrono>

class Treap {
private:
    // 1. CLASE NODO COMO ATRIBUTO PRIVADO (Inner Class)
    // Al estar aquí adentro, el usuario del Treap ni siquiera sabe que existe.
    class Node {
    private:
        int key;
        int priority;
        Node* left;
        Node* right;

    public:
        Node(int k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}

        int getKey() const { return key; }
        int getPriority() const { return priority; }
        void setPriority(int p) { priority = p; }
        Node* getLeft() const { return left; }
        void setLeft(Node* l) { left = l; }
        Node* getRight() const { return right; }
        void setRight(Node* r) { right = r; }
    };

    Node* root;
    std::mt19937 rng;

    // --- ROTACIONES ---
    void rotateRight(Node*& prnt) {
        Node* child = prnt->getLeft();
        prnt->setLeft(child->getRight());
        child->setRight(prnt);
        prnt = child; 
    }

    void rotateLeft(Node*& prnt) {
        Node* child = prnt->getRight();
        prnt->setRight(child->getLeft());
        child->setLeft(prnt);
        prnt = child; 
    }

    // 2. FUNCIÓN PARA ARREGLAR RECURSIVAMENTE (Balanceo)
    // Verifica si los hijos tienen mayor prioridad y rota. 
    // Al llamarse en cada paso de regreso de la recursión, empuja el nodo hasta donde deba llegar.
    void balance(Node*& t) {
        if (!t) return;

        if (t->getLeft() && t->getLeft()->getPriority() > t->getPriority()) {
            rotateRight(t);
        } else if (t->getRight() && t->getRight()->getPriority() > t->getPriority()) {
            rotateLeft(t);
        }
    }

    // --- OPERACIONES INTERNAS ---
    void insert(Node*& t, int key, int priority) {
        if (!t) {
            t = new Node(key, priority);
            return;
        }

        if (key < t->getKey()) {
            Node* l = t->getLeft();
            insert(l, key, priority);
            t->setLeft(l);
        } else if (key > t->getKey()) {
            Node* r = t->getRight();
            insert(r, key, priority);
            t->setRight(r);
        }

        // Llamamos a nuestra nueva función de arreglo en el camino de regreso
        balance(t);
    }

    // 3. NUEVA LÓGICA DE BÚSQUEDA
    bool searchAndUpdate(Node*& t, int key) {
        if (!t) return false;

        if (t->getKey() == key) {
            // Generamos un nuevo número aleatorio
            int new_priority = rng() % 100000;
            
            // Solo cambiamos si es mayor a la prioridad actual
            if (new_priority > t->getPriority()) {
                std::cout << "  [!] Prioridad aumentada de " << t->getPriority() 
                          << " a " << new_priority << std::endl;
                t->setPriority(new_priority);
            } else {
                std::cout << "  [-] La nueva prioridad (" << new_priority 
                          << ") no era mayor. Se mantiene igual." << std::endl;
            }
            return true;
        }

        bool found = false;
        if (key < t->getKey()) {
            Node* l = t->getLeft();
            found = searchAndUpdate(l, key);
            t->setLeft(l);
        } else {
            Node* r = t->getRight();
            found = searchAndUpdate(r, key);
            t->setRight(r);
        }

        // Si encontramos el nodo y potencialmente subió su prioridad, arreglamos el árbol al regresar
        if (found) {
            balance(t);
        }
        
        return found;
    }

    void erase(Node*& t, int key) {
        if (!t) return;

        if (key < t->getKey()) {
            Node* l = t->getLeft();
            erase(l, key);
            t->setLeft(l);
        } else if (key > t->getKey()) {
            Node* r = t->getRight();
            erase(r, key);
            t->setRight(r);
        } else {
            if (!t->getLeft() && !t->getRight()) {
                delete t;
                t = nullptr;
            } else if (!t->getLeft()) {
                Node* temp = t->getRight();
                delete t;
                t = temp;
            } else if (!t->getRight()) {
                Node* temp = t->getLeft();
                delete t;
                t = temp;
            } else {
                if (t->getLeft()->getPriority() > t->getRight()->getPriority()) {
                    rotateRight(t);
                    Node* r = t->getRight();
                    erase(r, key);
                    t->setRight(r);
                } else {
                    rotateLeft(t);
                    Node* l = t->getLeft();
                    erase(l, key);
                    t->setLeft(l);
                }
            }
        }
    }

    void inorder(Node* t) {
        if (!t) return;
        inorder(t->getLeft());
        std::cout << "[" << t->getKey() << " (p:" << t->getPriority() << ")] ";
        inorder(t->getRight());
    }

    void clear(Node* t) {
        if (!t) return;
        clear(t->getLeft());
        clear(t->getRight());
        delete t;
    }

public:
    Treap() : root(nullptr) {
        rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    }

    ~Treap() {
        clear(root);
    }

    void insert(int key) {
        int priority = rng() % 100000;
        insert(root, key, priority);
    }

    bool search(int key) {
        return searchAndUpdate(root, key);
    }

    void erase(int key) {
        erase(root, key);
    }

    void print() {
        if (!root) {
            std::cout << "Árbol vacío." << std::endl;
            return;
        }
        inorder(root);
        std::cout << "\n(Raíz actual: " << root->getKey() << " con prioridad " << root->getPriority() << ")\n" << std::endl;
    }
};
