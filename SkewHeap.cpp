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

template <class T>
T SkewHeap<T>::Node::value() const {
    return key;
}

template <class T>
typename SkewHeap<T>::Node* SkewHeap<T>::Node::parent() const {
    return father;
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

template <class T>
void SkewHeap<T>::mod_key(Node* node, T value) {
    if (value < node->key)
        decrease_key(node, value);
    else
        increase_key(node, value);
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
    //std::clog << " ** entry" << std::endl;
    //std::clog << " * parent: " << p << std::endl;
    if (n1 == nullptr || n2 == nullptr) {
        if (n1 == nullptr)
            std::swap(n1, n2);
    //std::clog << " * parent: " << p << std::endl;
    }

    // Recursive step
    else {
        //std::clog << " ** recursive step" << std::endl;
        if (n2->key < n1->key)
            std::swap(n1, n2);
            
        //std::clog << " * parent: " << p << std::endl;

        //std::clog << " * n1: " << n1 << std::endl;
        std::swap(n1->left, n1->right);
        n1->left = merge(n1->left, n2, n1);
    }
    n1->father = p;
    return n1;
}

template <class T>
void SkewHeap<T>::increase_key(Node* node, T value) {
    node->key = value;
    if (node->left->key < value) {
        Node* l = new Node(node->left->key, nullptr,
                           node->left->left, node->left->right);
        
        node->left = nullptr;
        merge(head, l);
    }
    if (node->right->key < value) {
        Node* r = new Node(node->right->key, nullptr,
                           node->right->left, node->right->right);

        node->right = nullptr;
        merge(head, r);
    }
}

template <class T>
void SkewHeap<T>::decrease_key(Node* node, T value) {
    node->key = value;
    if (value < node->father->key) {
        if (node->father->left == node)
            node->father->left = nullptr;
        else
            node->father->right = nullptr;
        
        node->father = nullptr;
        merge(head, node);
    }
}

/* ITERATOR IMPLEMENTATIONS */

template <class T>
SkewHeap<T>::Iterator::Iterator(Node* n) : current{n}, frontier{std::queue<Node*>()} {}

template <class T>
typename SkewHeap<T>::Iterator SkewHeap<T>::begin() const {
    SkewHeap<T>::Iterator it{head};
    return it;
}

template <class T>
typename SkewHeap<T>::Iterator SkewHeap<T>::end() const {
    SkewHeap<T>::Iterator it{nullptr};
    return it;
}

template <class T>
typename SkewHeap<T>::Iterator& SkewHeap<T>::Iterator::operator++() {
    if (current->left != nullptr)
        frontier.push(current->left);
    if (current->right != nullptr)
        frontier.push(current->right);
    
    if (!frontier.empty()) {
        current = frontier.front();
        frontier.pop();
    }
    else
        current = nullptr;
    
    return *this;
}

template <class T>
bool SkewHeap<T>::Iterator::operator!=(const SkewHeap::Iterator& other) const {
  return this->current != other.current;
}

template <class T>
T& SkewHeap<T>::Iterator::operator*() const {
  return current->key;
}

template class SkewHeap<int>;