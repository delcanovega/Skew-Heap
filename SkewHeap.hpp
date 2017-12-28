#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

template <class T>
class SkewHeap {
public:
    // Constructors
    SkewHeap(T root);
    SkewHeap(const SkewHeap& h);
    SkewHeap(SkewHeap* left, SkewHeap* root, SkewHeap* right);
    ~SkewHeap();

    SkewHeap& operator=(const SkewHeap&);

    // Main functions
    //SkewHeap* merge(SkewHeap* h1, SkewHeap* h2);
    //Data min() const;
    //bool insert(Data key);
    //bool delete_min();
    //bool mod_key(Node* node);

private:
    class Node {
    public:
        Node(T n)
          : key(n), father(nullptr), left(nullptr), right(nullptr) {}
        Node(T n, Node* f, Node* l, Node* r)
          : key(n), father(f), left(l), right(r) {}
        ~Node() {
            delete father;
            delete left;
            delete right;
        }

        Node(const Node& n);
        Node& operator=(const Node&);
        static Node* clone(Node const*);
        
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