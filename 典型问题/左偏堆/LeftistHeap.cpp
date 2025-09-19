/*
描述: 左偏堆，默认大根堆
参考: https://oi-wiki.org/ds/leftist-tree/
*/

#include <bits/stdc++.h>

using namespace std;

// 左偏堆，默认大根堆
template <typename T, typename Compare = std::less<T>>
class LeftistHeap {
private:
    struct Node {
        T key;
        int npl;
        Node* lc;
        Node* rc;
        // 这里的实现没定义 parent 指针
        Node(const T& k) : key(k), npl(1), lc(nullptr), rc(nullptr) {}
    };

    Node* root;
    Compare comp; // 比较器
    size_t _size;

    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;
        if (comp(a->key, b->key)) swap(a, b);
        a->rc = merge(a->rc, b);
        // 为什么不用判断 a->rc == nullptr? 走到这里，说明 a, b 都不为空，一开始的合并是合并到右子树的，所以swap之前右子树不会为空
        if (a->lc == nullptr || a->lc->npl < a->rc->npl) swap(a->lc, a->rc);
        a->npl = a->rc ? a->rc->npl + 1 : 1;
        return a;
    }

    void clear(Node* root) {
        if (root == nullptr) return;
        clear(root->lc);
        clear(root->rc);
        delete root;
    }

public:
    LeftistHeap() : root(nullptr), comp(Compare()), _size(0) {}
    explicit LeftistHeap(Compare comparator) : root(nullptr), comp(comparator), _size(0) {}
    ~LeftistHeap() { clear(root); }
    LeftistHeap(LeftistHeap&& other) noexcept : root(other.root), comp(std::move(other.comp)), _size(other._size) {
        other._size = 0;
        other.root = nullptr;
    }

    bool empty() const { return this->_size == 0; }

    size_t size() const { return this->_size; }

    const T& top() const {
        if (root == nullptr) throw runtime_error("LeftistHeap is empty");
        return root->key;
    }

    void pop() {
        if (root == nullptr) throw runtime_error("LeftistHeap is empty");
        this->_size--;
        Node* old_root = this->root;
        this->root = merge(this->root->lc, this->root->rc);
        delete old_root;
    }

    void push(const T& key) {
        this->_size++;
        root = merge(root, new Node(key));
    }

    void clear() {
        this->clear(this->root);
        this->_size = 0;
        this->root = nullptr;
    }

    void merge(LeftistHeap& other) {
        if (this == &other) return;
        this->root = merge(this->root, other.root);
        this->_size += other._size;
        other.root = nullptr;
        other._size = 0;
    }
};

int main(int argc, char const *argv[]) {
    LeftistHeap<int> heap;
    vector<int> arr = {1, 5, 2, 3, 8, 10, 9};
    for (int i = 0; i < arr.size(); i++) heap.push(arr[i]);
    while (heap.size() > 0) {
        cout << heap.top() << " ";
        heap.pop();
    }
    cout << endl;

    auto comp = [](auto& a, auto& b) {
        return a > b;
    };

    LeftistHeap<int, decltype(comp)> heap2(comp);
    for (int i = 0; i < arr.size(); i++) heap2.push(arr[i]);
    while (heap2.size() > 0) {
        cout << heap2.top() << " ";
        heap2.pop();
    }
    cout << endl;
    return 0;
}