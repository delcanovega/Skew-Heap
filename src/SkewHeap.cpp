#include "SkewHeap.hpp"

#include <algorithm>  // swap
#include <cassert>
#include <iostream>

template <class T>
SkewHeap<T>::SkewHeap()
  : root(nullptr),
    nodes(std::array<Node*, 100000>()),
    n(0)
{} 

template <class T>
SkewHeap<T>::SkewHeap(const T& x)
  : root(std::make_shared< Node >(x)),
    nodes(std::array<Node*, 100000>()),
    n(1)
{
    nodes[0] = root.get();
}

template <class T>
SkewHeap<T>::SkewHeap(const Node* n)
  : root(std::make_shared< Node >(n)),
    nodes(std::array<Node*, 100000>()),
    n(1)
{
    nodes[0] = root.get();
}

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

    nodes[n] = h.root.get();
    n++;

    merge(h);
}

template <class T>
void SkewHeap<T>::delete_min() {
    if (root)
        root = merge(root.get()->left, root.get()->right);

    // The smart pointers take care of the lost node automatically
}

template <class T>
void SkewHeap<T>::mod_key(Node* n, const T& k) {

    if (k < n->key)
        decrease_key(n, k);
    else if (k > n->key)
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
void SkewHeap<T>::increase_key(Node* n, const T& k) {
    n->key = k;

    Node* left = n->left.get();
    Node* right = n->right.get();
    
    SkewHeap<T> h1 = SkewHeap();
    SkewHeap<T> h2 = SkewHeap();

    if (left != nullptr && k > left->key) {
        left->parent = nullptr;

        h1 = SkewHeap(left);

        n->left.reset();
    }
    if (right != nullptr && k > right->key) {
        right->parent = nullptr;

        h2 = SkewHeap(right);

        n->right.reset();
    }

    h1.merge(h2);
    merge(h1);
}

template <class T>
void SkewHeap<T>::decrease_key(Node* n, const T& k) {
    n->key = k;

    Node* p = n->parent;
    if (p != nullptr && k < p->key) {
        n->parent = nullptr;

        SkewHeap<T> h = SkewHeap(n);

        if (p->left.get() == n)
            p->left.reset();
        else if (p->right.get() == n)
            p->right.reset();

        merge(h);
    }
    
}

template <class T>
void SkewHeap<T>::print() {
    if (root) {
        frontier.clear();
        route(root);  // BFS tour
    }
}

template <class T>
void SkewHeap<T>::route(Node_ptr& n) {
    std::cout << n.get()->key << "(";
    if (n.get()->parent != nullptr)
        std::cout << n.get()->parent->key << "), ";
    else
        std::cout << "-), ";
    
    if (n->left)
        frontier.push_back(n->left);
    if (n->right)
        frontier.push_back(n->right);
    
    if (frontier.empty()) {
        std::cout << std::endl;
        return;
    }

    Node_ptr next = frontier.front();
    frontier.pop_front();
    route(next);
}

template class SkewHeap<int>;