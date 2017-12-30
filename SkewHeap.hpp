#ifndef SKEW_HEAP_HPP_
#define SKEW_HEAP_HPP_

#include <queue>

template <class T>
class SkewHeap {
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

        T value() const;
        Node* parent() const;
        
        friend class SkewHeap;

    private:
        T key;
        Node* father;
        Node* left;
        Node* right;
    };

    Node* head;


    Node* merge(Node* n1, Node* n2, Node* parent = nullptr);
    void increase_key(Node* node, T value);
    void decrease_key(Node* node, T value);

public:
    // Constructors
    SkewHeap();
    SkewHeap(T root);
    SkewHeap(const SkewHeap& h);
    SkewHeap(SkewHeap&& h);
    ~SkewHeap();
    // Operators
    SkewHeap& operator=(const SkewHeap&);
    SkewHeap& operator=(SkewHeap&&);

    // Main functions
    void merge(SkewHeap* h);
    T min() const;
    void insert(T key);
    void delete_min();
    void mod_key(Node* node, T value);

    /* Iterator */
    using value_type = T;
    class Iterator {
    public:

        friend class Node;
        Iterator(Node* n);
        Iterator(Iterator&& other) = default;
        Iterator(const Iterator& other) = default;
        Iterator& operator=(Iterator&& other) = default;
        Iterator& operator=(const Iterator& other) = default;
        ~Iterator() = default;

        // Operators
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        T& operator*() const;
        
        Node* current{nullptr};
    
    private:

        std::queue<Node*> frontier;
    };

    Iterator begin() const;
    Iterator end() const;

};

#endif  // SKEW_HEAP_HPP_