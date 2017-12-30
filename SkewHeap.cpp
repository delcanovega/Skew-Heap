#include "SkewHeap.hpp"
#include <iostream>   // log
#include <algorithm>  // swap

/* NODE IMPLEMENTATIONS */

template <class T>
typename SkewHeap<T>::Node* SkewHeap<T>::Node::clone(Node* dolly, Node* father) {
    if (dolly == nullptr)
        return nullptr;
    else {
        Node* me = new Node(dolly->key, father);
        me->left = clone(dolly->left, me);
        me->right = clone(dolly->right, me);

        return me;
    }
}

/* SKEW HEAP IMPLEMENTATIONS */

// Main operations:

template <class T>
void SkewHeap<T>::merge(SkewHeap* h) {
    // this function is just a wrapper
    // nullptr handling inside the recursive function
    head = merge(head, h->head);  // recursive function
}

template <class T>
T SkewHeap<T>::min() const {
    // TODO: Error handling
    return head->key;
}

template <class T>
void SkewHeap<T>::insert(T k) {
    SkewHeap<T>* h = new SkewHeap(k);
    merge(h);
}

template <class T>
void SkewHeap<T>::delete_min() {
    // TODO: Error handling
    head = merge(head->left, head->right);
}

// Constructors, destructors & operators:

template <class T>
SkewHeap<T>::SkewHeap() : head(nullptr) {
    std::clog << "***Default empty construction" << std::endl;
}

template <class T>
SkewHeap<T>::SkewHeap(T root) : head(new Node(root)) {
    std::clog << "***Default construction" << std::endl;
}

template <class T>
SkewHeap<T>::SkewHeap(const SkewHeap& h) : head(Node::clone(h.head)) {
    std::clog << "***Copy construction" << std::endl;
    //head = Node::clone(h.head);
}

template <class T>
SkewHeap<T>::SkewHeap(SkewHeap&& h) : head(h.head) {
  std::clog << "***Move construction" << std::endl;
  //head = h.head;
  h.head = nullptr;
}

template <class T>
SkewHeap<T>::~SkewHeap() {
    delete head;  // Should I iterate the whole data structure?
}

template <class T>
SkewHeap<T>& SkewHeap<T>::operator=(const SkewHeap& rhs) {
  std::clog << "***Copy assignment" << std::endl;
  if (&rhs != this)
  {
    SkewHeap copy(rhs);
    std::swap(head, copy.head);
  }
  return *this;
}

template <class T>
SkewHeap<T>& SkewHeap<T>::operator=(SkewHeap&& rhs) {
  std::clog << "***Move assignment" << std::endl;
  if (&rhs != this)
  {
    std::swap(head, rhs.head);
  }
  return *this;
}

// Auxiliar functions:
/*
template <class T>
void SkewHeap<T>::decompose(SkewHeap& h, SkewHeap& l, SkewHeap& r) {
    // Emancipate the child into the new heaps
    l.head = h.head->left;
    l.head->father = nullptr;

    r.head = h.head->right;
    r.head->father = nullptr;

    // Isolate the root
    h.head->left = nullptr;
    h.head->right = nullptr;
}
*/
template <class T>
typename SkewHeap<T>::Node* SkewHeap<T>::merge(Node* n1, Node* n2, Node* p) {
    // Base case
    if (n1 == nullptr || n2 == nullptr) {
        if (n1 == nullptr)
            std::swap(n1, n2);
    }
    // Recursive step
    else {
        if (n2->key < n1->key)
            std::swap(n1, n2);

        n1->father = p;
        std::swap(n1->left, n1->right);
        n1->left = merge(n1->left, n2, n1);
    }
    return n1;
}


/* ... */

template class SkewHeap<int>;