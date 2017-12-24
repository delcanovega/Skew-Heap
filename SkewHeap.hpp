#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

//#include <vector>  // Only for the special constructor
/*
template<class T>
class Node {
public:
    Node(Data key);

    Data key;
    Node* left_son{nullptr};
    Node* right_son{nullptr};
    Node* father{nullptr};
};*/

template<class T>
class SkewHeap {
public:
    // Constructors
    SkewHeap(T root);
    //SkewHeap(const std::vector<T>& v);
    SkewHeap(SkewHeap* left, SkewHeap* root, SkewHeap* right);

    // Main functions
    SkewHeap* merge(SkewHeap* h1, SkewHeap* h2);
    //Data min() const;
    //bool insert(Data key);
    //bool delete_min();
    //bool mod_key(Node* node);

private:
    struct node {
        T key;
        node* father;
        node* left;
        node* right;
    };

    node* head;

    // Auxiliar functions
    void decompose(SkewHeap* left, SkewHeap* right);
    //SkewHeap left() const;
    //SkewHeap right() const;

    //void set_left(SkewHeap* heap);
    //void set_right(SkewHeap* heap);

};

#endif  // SKEW_HEAP_HPP_