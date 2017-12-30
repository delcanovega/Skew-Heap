#include "SkewHeap.hpp"
#include <iostream>  // For log

/* NODE IMPLEMENTATIONS */

template <class T>
typename SkewHeap<T>::Node* SkewHeap<T>::Node::clone(const Node* dolly, const Node* father = nullptr) {
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
void SkewHeap<T>::merge(SkewHeap& h) {
    if (head == nullptr) {
        head = h.head;
        h.head = nullptr;
        return;
    }
    else if (h2.head == nullptr) {
        return;
    }
    else {
        SkewHeap l, r;
        if (head->key < h.head->key) {
            decompose(this, l, r);
            merge();
            return SkewHeap(merge(r, h2), h1, l);
        }
        else {
            decompose(h2, l, r);
            return SkewHeap(merge(r, h1), h2, l);
        }
    }
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
SkewHeap<T>::SkewHeap(SkewHeap&& h){
  std::clog << "***Move construction" << std::endl;
  head = h.head;
  h.head = nullptr;
}

template <class T>
SkewHeap<T>::~SkewHeap() {
    delete head;  // Should I iterate the whole data structure?
}

template <class T>
SkewHeap<T>& SkewHeap<T>::operator=(const SkewHeap& rhs)
{
  std::clog << "***Copy assignment" << std::endl;
  if (&rhs != this)
  {
    SkewHeap copy(rhs);
    std::swap(head, copy.head);
  }
  return *this;
}

template <class T>
SkewHeap<T>& SkewHeap<T>::operator=(SkewHeap&& rhs)
{
  std::clog << "***Move assignment" << std::endl;
  if (&rhs != this)
  {
    std::swap(head, rhs.head);
  }
  return *this;
}

// Auxiliar functions:

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




/* ... */

template class SkewHeap<int>;