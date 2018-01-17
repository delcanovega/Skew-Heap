#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

#include <memory>  // for smart pointers
#include <deque>   // print

template <class T>
class SkewHeap {
private:
    struct Node {
        T key;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        Node* parent;

        Node(const T& x) : key(x), left(nullptr), right(nullptr), parent(nullptr) {}
        Node(const Node* n)
        : key(n->key),
            left(n->left),
            right(n->right),
            parent(n->parent) 
        {}
    };

    typedef std::shared_ptr< Node > Node_ptr;

    Node_ptr root;

    Node_ptr merge(Node_ptr& h1, Node_ptr& h2, Node* p = nullptr);
    void increase_key(Node* node, const T& value);
    void decrease_key(Node* node, const T& value);

    void route(Node_ptr& n);
    void pretty_print();

    std::deque<Node_ptr> frontier;

public:
    SkewHeap();
    SkewHeap(const T& x);
    SkewHeap(const Node* n);

    // Main functions
    void merge(SkewHeap& h);
    T min() const;
    void insert(const T& key);
    void delete_min();
    void mod_key(const T& value);

    //Node* get_node() const;
    void print();
};

#endif  // SKEW_HEAP_HPP_