#include "SkewHeap.hpp"

/* SKEW HEAP IMPLEMENTATIONS */

template <class T>
SkewHeap<T>::SkewHeap(T root)
  : head(Node(root)) {}

template <class T>
SkewHeap<T>::~SkewHeap() {
}

template class SkewHeap<int>;