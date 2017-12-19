#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

#include <vector>  // Only for the special constructor

template<typename Data>
class Node {
public:
    Node(Data key);

    Data key;
    Node* left_son{nullptr};
    Node* right_son{nullptr};
    Node* father{nullptr};
};

template<typename Data>
class SkewHeap {
public:
    // Constructors
    SkewHeap(Data root);
    SkewHeap(std::vector<Data> v);

    // Main functions
    SkewHeap merge(SkewHeap* l_heap, SkewHeap* r_heap);
    Data min() const;
    bool insert(Data key);
    bool delete_min();
    bool mod_key(Node* node);

    int size() const;
    Data key() const;
    void swap_child();
    SkewHeap left_son() const;
    SkewHeap right_son() const;

    void l_son(SkewHeap* heap);

private:
    int size{0};
    Node* root{nullptr};

};

#endif  // SKEW_HEAP_HPP_