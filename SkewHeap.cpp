#include "SkewHeap.hpp"

/* NODE IMPLEMENTATION */
/*
template<typename Data>
Node<Data>::Node(Data value) : key{value}, left_son{nullptr}, right_son{nullptr},
    father{nullptr} {}
*/

/* SKEW HEAP IMPLEMENTATION */

// Constructors
template<class T>
SkewHeap<T>::SkewHeap(T value) {
    root = new node;
    root->key = value;
    root->father = nullptr;
    root->left = nullptr;
    root->right = nullptr;
}
/*
template<typename Data>
SkewHeap<Data>::SkewHeap(const std::vector<Data>& v) : root{nullptr} {
    SkewHeap* tmp{nullptr};

    auto it = v.cbegin();
    tmp = SkewHeap(*it);
    it++;
    for (it; it != v.cend(); it++) {
        tmp = merge(tmp, SkewHeap(*it));
    }

    this = tmp;
}

template<typename Data>
SkewHeap<Data>::SkewHeap(SkewHeap* h1, Data* node, SkewHeap* h2) : size{1}, root{node} {
    set_left_son(h1);
    set_right_son(h2);
}

// Main functions
template<typename Data>
SkewHeap<Data>::SkewHeap *merge(SkewHeap* h1, SkewHeap* h2) {
    
    if (h1 == nullptr) {
        return *h2;
    }
    else if (h2 == nullptr) {
        return *h1;
    }

    else {
        if (h1->key() < h2->key()) {
            SkewHeap* l1{h1->left_son()};
            SkewHeap* r1{h1->right_son()};

            return SkewHeap( merge(r1, h2), h1->root, l1);
        }
        else {
            SkewHeap* l2{h2->left_son()};
            SkewHeap* r2{h2->right_son()};

            return SkewHeap( merge(r2, h1), h2->root, l2);
        }
    }
}

template<typename Data>
Data SkewHeap<Data>::min() const {
    return root->key;
}

// Auxiliar functions
template<typename Data>
void SkewHeap<Data>::set_left_son(SkewHeap* heap) {
    root->left_son = heap;
}

template<typename Data>
void SkewHeap<Data>::set_right_son(SkewHeap* heap) {
    root->right_son = heap;
}

template<typename Data>
SkewHeap SkewHeap<Data>::left_son() const {
    return SkewHeap(root->left_son);
}

template<typename Data>
SkewHeap SkewHeap<Data>::right_son() const {
    return SkewHeap(root->right_son);
}
*/