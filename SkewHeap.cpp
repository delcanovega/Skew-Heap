#include "SkewHeap.hpp"

/* NODE IMPLEMENTATIONS */

template <class T>
SkewHeap<T>::Node::Node(T const& n)
  : key(n), father(nullptr), left(nullptr), right(nullptr) {}

template <class T>
SkewHeap<T>::Node::~Node() {
    delete father;
    delete left;
    delete right;
}

/* SKEW HEAP IMPLEMENTATIONS */

template <class T>
SkewHeap<T>::SkewHeap(T root)
  : head(Node(root)) {}

template <class T>
SkewHeap<T>::~SkewHeap() {
    delete head;
}