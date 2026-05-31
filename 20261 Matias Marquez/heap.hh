#ifndef HEAP_HH
#define HEAP_HH
#include <iostream>
#include "Vector.hh"
using namespace std;



template <typename K, typename V>
class MinBinaryHeap {
private:
    Vector<pair<K, V>> heap;
    unsigned int sz;

public:

    MinBinaryHeap() {
        heap.push_back({K(), V()});
        sz = 0;
    }


    void insert(K key, V value) {
        heap.push_back({key, value});
        sz++ ;
        heapifyUp(heap.size() - 1);
    }

    pair<K, V> extractMin() {
        if (empty()) {
            return {K(), V()};
        }
       pair<K, V> minElement = heap[1];
        heap[1] = heap.back();
        heap.pop_back();
        if (heap.size() > 1) {
            heapifyDown(1);
        }
        sz--;
        return minElement;
    }

   
    bool empty() const {
        return heap.size() <= 1; 
    }

private:
      
    void heapifyUp(int index) {
        if (index <= 1) return;
        int parent = index / 2;
        if (heap[index].first < heap[parent].first) {
            heap.swap(index, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index;
        int rightChild = 2 * index + 1;
        int smallest = index; 

        if (leftChild < heap.size() && heap[leftChild].first < heap[smallest].first) {
            smallest = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild].first < heap[smallest].first) {
            smallest = rightChild;
        }
        if (smallest != index) {
            heap.swap(index, smallest);
            heapifyDown(smallest);
        }
    }
};

#endif