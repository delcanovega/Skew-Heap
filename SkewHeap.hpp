#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

template <class T>
class SkewHeap {
public:
    // Constructors
    SkewHeap(T root);
    SkewHeap(const SkewHeap<T>& h);
    SkewHeap(SkewHeap* left, SkewHeap* root, SkewHeap* right);
    ~SkewHeap();

    SkewHeap& operator=(const SkewHeap&);

    // Main functions
    SkewHeap* merge(SkewHeap* h1, SkewHeap* h2);
    //Data min() const;
    //bool insert(Data key);
    //bool delete_min();
    //bool mod_key(Node* node);
    void print() const;

private:
    class Node {
    public:
        Node(const T& n);
        ~Node();
        
        friend class SkewHeap;

    private:
        T key;
        Node* father;
        Node* left;
        Node* right;
    };

    Node* head;

};

#endif  // SKEW_HEAP_HPP_