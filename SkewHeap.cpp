#include "SkewHeap.hpp"
#include <iostream>  // For log

/* NODE IMPLEMENTATIONS */

template <class T>
typename SkewHeap<T>::Node* SkewHeap<T>::Node::clone(const Node* dolly) {
    if (dolly == nullptr)
        return nullptr;
    else {
        // preorder (?)
        return new Node(dolly->key, clone(dolly->father),
                        clone(dolly->left), clone(dolly->right));
    }
}

/* SKEW HEAP IMPLEMENTATIONS */

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
SkewHeap<T>::~SkewHeap() {
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






/* *...*/

template class SkewHeap<int>;