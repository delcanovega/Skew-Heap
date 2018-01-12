#include "SkewHeap.hpp"

#include <algorithm>  // swap

template <class T>
SkewHeap<T>::SkewHeap(const T& x) : root(std::make_shared< Node<T> >(x)) {}

template <class T>
void SkewHeap<T>::merge(SkewHeap& h) {
    // this function is just a wrapper
    // nullptr handling inside the recursive function
    root = merge(root, h.root);  // recursive function
}

template <class T>
T SkewHeap<T>::min() const {
    if (root)
        return root->key;
    else
        return -1;
}

template <class T>
void SkewHeap<T>::insert(const T& k) {
    SkewHeap<T> h = SkewHeap(k);
    merge(h);
}

template <class T>
void SkewHeap<T>::delete_min() {
    if (root)
        root = merge(root.get()->left, root.get()->right);

    // The smart pointers handle the lost root automatically
}

template <class T>
void SkewHeap<T>::mod_key(Node_ptr& n, const T& k) {
    if (!n)
        return;
    
    if (k < n.get()->key)
        decrease_key(n, k);
    else if (k > n.get()->key)
        increase_key(n, k);
}

// Auxiliar functions:

template <class T>
typename SkewHeap<T>::Node_ptr SkewHeap<T>::merge(Node_ptr& h1, Node_ptr& h2, Node<T>* p) {
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
void SkewHeap<T>::decrease_key(Node_ptr& n, const T& k) {
    n.get()->key = k;

    Node_ptr l = n.get()->left;
    if (l && k < l.get()->key) {
        l.get()->parent = nullptr;
        n.get()->left = nullptr;
    }
    Node_ptr r = n.get()->right;
    if (r && k < r.get()->key) {
        r.get()->parent = nullptr;
        n.get()->right = nullptr;
    }

    if (l && k < l.get()->key)
        merge(root, l);
    if (r && k < r.get()->key)
        merge(root, r);
}

template <class T>
void SkewHeap<T>::increase_key(Node_ptr& n, const T& k) {
    n.get()->key = k;

    Node<T>* p = n.get()->parent;
    if (p != nullptr && p->key < k) {
        n.get()->parent = nullptr;

        if (p->left.get() == n.get())
            p->left.reset();
        else
            p->right.reset();

        merge(root, n);
    }
    
}

template class SkewHeap<int>;