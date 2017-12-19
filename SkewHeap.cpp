#include "SkewHeap.hpp"

Node::Node(int value) : key{value}, left_son{nullptr}, right_son{nullptr},
    father{nullptr} {}

SkewHeap::SkewHeap(int value) : size{1}, root{&Node{value}} {}

SkewHeap::SkewHeap merge(SkewHeap* l_heap, SkewHeap* r_heap) {
    
    if (l_heap == nullptr) {
        return *r_heap;
    }
    else if (r_heap == nullptr) {
        return *l_heap;
    }

    SkewHeap* tmp;
    if (l_heap->key() < r_heap->key()) {
        tmp = l_heap;
        tmp->swap_child();
        tmp->l_son( &merge(&l_heap->left_son(), r_heap) );
    }
}

int SkewHeap::min() const {
    return root->key;
}