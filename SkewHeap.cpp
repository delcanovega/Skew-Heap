#include "SkewHeap.hpp"

/* NODE IMPLEMENTATION */

template<typename Data>
Node::Node(Data value) : key{value}, left_son{nullptr}, right_son{nullptr},
    father{nullptr} {}


/* SKEW HEAP IMPLEMENTATION */

// Constructors
template<typename Data>
SkewHeap::SkewHeap(Data value) : size{1}, root{&Node{value}} {}

template<typename Data>
SkewHeap::SkewHeap(std::vector<Data> v) : size{v.size()}, root{nullptr} {
    SkewHeap* tmp{nullptr};

    auto it = v.cbegin();
    tmp = SkewHeap(*it);
    it++;
    for (it; it != v.cend(); it++) {
        tmp = tmp.merge(tmp, SkewHeap(*it));
    }

    root = tmp;
}

template<typename Data>
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
    /* ... */
}

template<typename Data>
Data SkewHeap::min() const {
    return root->key;
}