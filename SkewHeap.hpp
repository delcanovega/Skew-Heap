#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

template <class T>
class SkewHeap {
public:
    // Constructors
    SkewHeap();
    SkewHeap(T root);
    SkewHeap(const SkewHeap& h);
    SkewHeap(SkewHeap* left, SkewHeap* root, SkewHeap* right);
    ~SkewHeap();

    SkewHeap& operator=(const SkewHeap&);

    // Main functions
    void merge(SkewHeap& h);
    //Data min() const;
    //bool insert(Data key);
    //bool delete_min();
    //bool mod_key(Node* node);

private:
    class Node {
    public:
        Node(T n, Node* f = nullptr, Node* l = nullptr, Node* r = nullptr)
          : key(n), father(f), left(l), right(r) {}
        ~Node() {
            delete father;
            delete left;
            delete right;
        }

        Node(const Node& n);
        Node& operator=(const Node&);
        static Node* clone(const Node*, const Node*);
        
        friend class SkewHeap;

    private:
        T key;
        Node* father;
        Node* left;
        Node* right;
    };

    Node* head;

    void decompose(SkewHeap& h, SkewHeap& l, SkewHeap& r);
};

#endif  // SKEW_HEAP_HPP_