#include "LIST.hh"

template<typename T>
class Queue {
private:
    List<T> storage; 
public:
    Queue() : storage() {}
    Queue(const Queue<T>& other) : storage(other.storage) {}
    ~Queue() {}
    bool empty() const {
        return storage.empty();
    }
    unsigned int size() const {
        return storage.size();
    }
    void push(const T& elem) {
        storage.push_back(elem);
    }
    void pop() {
        assert(!empty());
        storage.pop_front();
    }
    const T& front() const {
        assert(!empty());
        return storage.at_node(0)->get_data();
    }};