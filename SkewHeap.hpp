#ifndef SSKEW_HEAP_HPP_
#define SSKEW_HEAP_HPP_

#include <memory>  // for smart pointers
#include <iostream>  // test

template <class T>
struct Node {
    T key;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node* parent;

    Node(const T& x) : key(x), left(nullptr), right(nullptr) {}
};

template <class T>
class SkewHeap {
    typedef std::shared_ptr< Node<T> > Node_ptr;
    Node_ptr root;

    Node_ptr merge(Node_ptr& h1, Node_ptr& h2, Node<T>* p = nullptr);
    void increase_key(Node_ptr& node, const T& value);
    void decrease_key(Node_ptr& node, const T& value);

public:
    SkewHeap(const T& x);
    SkewHeap(Node_ptr&& n);

    // Main functions
    void merge(SkewHeap& h);
    T min() const;
    void insert(const T& key);
    void delete_min();
    void mod_key(Node_ptr& node, const T& value);

    void test() {
        std::cout << root.get()->key << " (-) ";
        std::cout << root.get()->left.get()->key << " (";
        std::cout << root.get()->left.get()->parent->key << ") ";
        std::cout << std::endl;
    }
};

#endif  // SSKEW_HEAP_HPP_