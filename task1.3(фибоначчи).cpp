// Пример кода с реализацией «кучи Фибоначчи» на C++
#ifndef FIBONACCI_HEAP_HPP
#define FIBONACCI_HEAP_HPP
#include <vector>
#include <list>
#include <math.h>
typedef long long int lli;
#define GOLDEN_RATIO_ROUND_DOWN 1.618
template <class V> class FibonacciHeap;
template<class T>
class Element {
    protected:
    Element<T> *left = this;
    Element<T> *right = this;
    Element<T> *parent = nullptr;
    Element<T> *child = nullptr;
    T key;
    lli degree = 0;
    bool mark = false;
    public:
    Element(T key) : key(key) {};
    Element(Element<T> *other) : key(other->key), degree(other->degree), mark(other->mark) {
        this->left = other->left;
        this->right = other->right;
        this->parent = other->parent;
        this->child = other->child;
    }
    T getKey() { return this->key; }
    Element<T> *getLeft() { return this->left; }
    Element<T> *getRight() { return this->right; }
    Element<T> *getChild() { return this->child; }
    Element<T> *getParent() { return this->parent; }
    bool isMarked() { return this->mark; }
    lli getDegree() { return this->degree; }
    friend class FibonacciHeap<T>;
};
template<class T>
class FibonacciHeap {
    private:
    // Copy constructor and assignment operator are not implemented
// Hiding them to avoid misusage (Rule of three)
// Since the point here is show the algorithmic part of the data structure
    FibonacciHeap(const FibonacciHeap<T> &other);
    FibonacciHeap<T> &operator=(const FibonacciHeap<T> &other);
    protected:
    Element<T> *min;
    lli n;
    lli _D(lli n) {
        return log(n)/log(GOLDEN_RATIO_ROUND_DOWN);
    }
    void _deleteAll(Element<T> *x) {
        if (x != nullptr) {
            Element<T> *y = x;
            do {
                Element<T> *z = y;
                y = y->right;
                this->_deleteAll(z->child);
                delete z;
            } while (y != x);
        }
    }
    Element<T> *_unite(Element<T> *x, Element<T> *y) {
        if (x == nullptr) {
            return y;
        } else if (y == nullptr) {
            return x;
        } else if (x->key > y->key) {
            return this->_unite(y, x);
        } else {
            Element<T> *xRight = x->left;
            Element<T> *yRight = y->left;
            x->left = yRight;
            xRight->right = y;
            y->left = xRight;
            yRight->right = x;
            return x;
        }
    }
    void _link(Element<T> *y, Element<T> *x) {
        y->left->right = y->right;
        y->right->left = y->left;
        if (x->child == nullptr) {
            x->child = y;
            y->right = y;
            y->left = y;
        } else {
            Element<T> *child = x->child;
            y->right = child;
            y->left = child->left;
            child->left->right = y;
            child->left = y;
        }
        y->parent = x;
        x->degree++;
        y->mark = false;
    }
    void _fillListWithElements(Element<T> *x, std::list<Element<T>*> &A) {
        Element<T> *last = x;
        Element<T> *w = last;
        do {
            w = w->right;
            A.push_back(w);
        } while (w != last);
    }
    void _consolidate() {
        lli D = this->_D(this->n);
        std::vector<Element<T>*> A(D + 1, nullptr);
        std::list<Element<T>*> elements;
        this->_fillListWithElements(this->min, elements);
        for (auto x : elements) {
            lli d = x->degree;
            while (A.at(d) != nullptr) {
                Element<T> *y = A.at(d);
                if (x->key > y->key) {
                    std::swap(x, y);
                }
                this->_link(y, x);
                A.at(d) = nullptr;
                d++;
            }
            A.at(d) = x;
        }
        this->min = nullptr;
        for (lli i = 0; i < (lli)A.size(); i++) {
            if (A.at(i) != nullptr) {
                A.at(i)->right = A.at(i);
                A.at(i)->left = A.at(i);
                this->min = this->_unite(this->min, A.at(i));
            }
        }
    }
    void _cut(Element<T> *x, Element<T> *y) {
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x) {
            if (x->right == x) {
                y->child = nullptr;
            } else {
                y->child = x->right;
            }
        }
        y->degree--;
        x->left = x;
        x->right = x;
        x->parent = nullptr;
        x->mark = false;
        this->min = this->_unite(this->min, x);
    }
    void _cascadingCut(Element<T> *y) {
        Element<T> *z = y->parent;
        if (z != nullptr) {
            if (!y->mark) {
                y->mark = true;
            } else {
                this->_cut(y, z);
                this->_cascadingCut(z);
            }
        }
    }
    public:
    FibonacciHeap() {
    }
    this->min = nullptr;
this->n = 0;
};
~FibonacciHeap() {
    if (this->min != nullptr) {
        this->_deleteAll(this->min);
    }
}
bool isEmpty() const {
        return this->min == nullptr;
}
Element<T> *insert(T key) {
    Element<T> *x = new Element<T>(key);
    this->min = this->_unite(this->min, x);
    this->n++;
    return x;
}
void unite(FibonacciHeap<T> *heap) {
    this->min = this->_unite(this->min, heap->min);
    this->n += heap->n;
    heap->min = nullptr;
    heap->n = 0;
}
T getMin() const {
        return this->min->key;
}
T extractMin() {
    Element<T> *z = this->min;
    if (z == nullptr) {
        throw std::invalid_argument("heap is empty");
    }
    Element<T> *x = z->child;
    if (x != nullptr) {
        Element<T> *last = x;
        do {
            x = x->right;
            x->parent = nullptr;
        } while (x != last);
        this->min = this->_unite(this->min, x);
    }
    z->left->right = z->right;
    z->right->left = z->left;
    if (z == z->right) {
        this->min = nullptr;
    } else {
        this->min = z->right;
        this->_consolidate();
    }
    this->n--;
    T min = z->key;
    delete z;
    return min;
}
void decreaseKey(Element<T>* x, T k) {
    if (k > x->key) {
        throw std::invalid_argument("new key is greater than current key");
    }
    x->key = k;
    Element<T> *y = x->parent;
    if (y != nullptr && x->key < y->key) {
        this->_cut(x, y);
        this->_cascadingCut(y);
    }
    if (x->key < this->min->key) {
        this->min = x;
    }
}
void deleteElement(Element<T> *x) {
    this->decreaseKey(x, std::numeric_limits<T>::min());
    this->extractMin();
} 
}