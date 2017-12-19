#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

class Node {
public:
    Node(int key);

    int key;
    Node* left_son{nullptr};
    Node* right_son{nullptr};
    Node* father{nullptr};
};

class SkewHeap {
public:
    SkewHeap(int root);

    SkewHeap merge(SkewHeap* l_heap, SkewHeap* r_heap);
    int min() const;
    bool insert(int key);
    bool delete_min();
    bool mod_key(Node* node);

    int size() const;
    int key() const;
    void swap_child();
    SkewHeap left_son() const;
    SkewHeap right_son() const;

    void l_son(SkewHeap* heap);

private:
    int size{0};
    Node* root{nullptr};

};

#endif  // SKEW_HEAP_HPP_