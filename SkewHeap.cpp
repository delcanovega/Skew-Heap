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
    head = new node;
    head->key = value;
    head->father = nullptr;
    head->left = nullptr;
    head->right = nullptr;
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
*/
template<class T>
SkewHeap<T>::SkewHeap(SkewHeap* left, SkewHeap* root, SkewHeap* right) {
    head = new node;
    head = root->head;
    head->left = left->head;
    head->right = right->head;
}

// Main functions
template<class T>
SkewHeap<T>* SkewHeap<T>::merge(SkewHeap* h1, SkewHeap* h2) {
    
    if (h1 == nullptr) {
        return *h2;
    }
    else if (h2 == nullptr) {
        return *h1;
    }

    else {
        SkewHeap* l, r;
        if (h1->key() < h2->key()) {
            h1->decompose(l, r);

            return SkewHeap( merge(r, h2), h1, l);
        }
        else {
            h2->decompose(l, r);  // returns the root node of h2

            return SkewHeap( merge(r, h1), h2, l);
        }
    }
}
/*
template<typename Data>
Data SkewHeap<Data>::min() const {
    return root->key;
}
*/
// Auxiliar functions
template<class T>
void SkewHeap<T>::decompose(SkewHeap* left, SkewHeap* right) {
    left->head = head->left;
    left->head->father = nullptr;

    right->head = head->right;
    right->head->father = nullptr;

    head->left = nullptr;
    head->right = nullptr;
}

/*
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