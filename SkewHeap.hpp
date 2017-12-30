#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

template <class T>
class SkewHeap {
public:
    // Constructors
    SkewHeap();
    SkewHeap(T root);
    SkewHeap(const SkewHeap& h);
    SkewHeap(SkewHeap&& h);
    SkewHeap(SkewHeap* left, SkewHeap* root, SkewHeap* right);
    ~SkewHeap();

    SkewHeap& operator=(const SkewHeap&);
    SkewHeap& operator=(SkewHeap&&);

    // Main functions
    void merge(SkewHeap* h);
    T min() const;
    void insert(T key);
    void delete_min();
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
        static Node* clone(Node* dolly, Node* father = nullptr);
        
        friend class SkewHeap;

    private:
        T key;
        Node* father;
        Node* left;
        Node* right;
    };

    Node* head;

    //void decompose(SkewHeap* h, SkewHeap* l, SkewHeap* r);
    Node* merge(Node* n1, Node* n2, Node* parent = nullptr);
};

#endif  // SKEW_HEAP_HPP_