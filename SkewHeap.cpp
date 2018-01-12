#include "SSkewHeap.hpp"

#include <algorithm>  // for swap

template <class T>
SkewHeap<T>::SkewHeap(const T& x) : root(std::make_shared<Node>(x)) {}

template <class T>
void SkewHeap<T>::merge(SkewHeap& h) {
    // this function is just a wrapper
    // nullptr handling inside the recursive function
    root = merge(root, h.root);  // recursive function
}

template <class T>
T SkewHeap<T>::min() const {
    // TODO: Error handling
    return root->key;
}

template <class T>
void SkewHeap<T>::insert(const T& k) {
    SkewHeap<T> h = SkewHeap(k);
    merge(h);
}

template <class T>
void SkewHeap<T>::delete_min() {
    // TODO: Error handling
    root = merge(root.get()->left, root.get()->right);
}

template <class T>
void SkewHeap<T>::mod_key(Node_ptr n, const T& k) {
    if (!n)
        return;
    
    if (k < n.get()->key)
        decrease_key(n, k);
    else if (k > n.get()->key)
        increase_key(n, k);
}

// Auxiliar functions:

template <class T>
typename SkewHeap<T>::Node_ptr SkewHeap<T>::merge(Node_ptr& h1, Node_ptr& h2, Node* p) {
    // Base case:
    if (!h1 || !h2) {
        if (!h1) {
            std::swap(h1, h2);
            if (h1)
                h1.get()->parent = p;
        }
    }
    // Recursive step:
    else {
        if (h2.get()->key < h1.get()->key) {  // We always want to work with h1
            std::swap(h1.get()->parent, h2.get()->parent);
            std::swap(h1, h2);
        }  // we have exchanged the keys and sons, but maintaining the parents
        
        std::swap(h1.get()->left, h1.get()->right);
        h1.get()->parent = p;
        h1.get()->left = merge(h1.get()->left, h2, h1.get());
    }

    return h1;
}

template <class T>
void SkewHeap<T>::decrease_key(Node_ptr n, const T& k) {

}

template <class T>
void SkewHeap<T>::increase_key(Node_ptr n, const T& k) {
    
}

template class SkewHeap<int>;