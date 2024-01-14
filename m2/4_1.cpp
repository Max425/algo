#include <iostream>
#include <queue>

template <class T, class Compare>
class AVLtree
{
public:
    AVLtree(const Compare &_cmp) : root(nullptr), cmp(_cmp) {}
    ~AVLtree()
    {
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *next = q.front();
            q.pop();
            if (next->Left)
                q.push(next->Left);
            if (next->Right)
                q.push(next->Right);
            delete next;
        }
    }

    AVLtree(const AVLtree &) = delete;
    AVLtree &operator=(const AVLtree &) = delete;

    void Add(const T &key) { add(root, key); }
    void Remove(const T &key) { root = remove(root, key); }
    int FindKStatistic(const T &key) { return findKStatistic(root, key); }
    T FindKElement(int statistic) { return findKElement(root, statistic); }

private:
    struct Node
    {
        Node *Left;
        Node *Right;
        unsigned char Height;
        unsigned int Count;
        T Key;
        Node(const T &key) : Left(nullptr), Right(nullptr), Key(key), Height(1), Count(1) {}
    };
    Node *root;
    Compare cmp;

    unsigned char height(Node *p) { return p ? p->Height : 0; }
    unsigned int count(Node *p) { return p ? p->Count : 0; }
    int bfactor(Node *p) { return height(p->Right) - height(p->Left); }
    void fixHeightAndCount(Node *p)
    {
        auto hl = height(p->Left);
        auto hr = height(p->Right);
        p->Height = (hl > hr ? hl : hr) + 1;

        p->Count = count(p->Left) + count(p->Right) + 1;
    }
    Node *rotateRight(Node *p)
    {
        Node *q = p->Left;
        p->Left = q->Right;
        q->Right = p;
        fixHeightAndCount(p);
        fixHeightAndCount(q);
        return q;
    }
    Node *rotateLeft(Node *q)
    {
        Node *p = q->Right;
        q->Right = p->Left;
        p->Left = q;
        fixHeightAndCount(q);
        fixHeightAndCount(p);
        return p;
    }
    Node *balance(Node *&p)
    {
        fixHeightAndCount(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->Right) < 0)
                p->Right = rotateRight(p->Right);
            return rotateLeft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->Left) > 0)
                p->Left = rotateLeft(p->Left);
            return rotateRight(p);
        }
        return p;
    }
    void add(Node *&p, const T &key)
    {
        if (!p)
            p = new Node(key);
        else if (cmp(key, p->Key))
            add(p->Left, key);
        else
            add(p->Right, key);
        p = balance(p);
    }
    Node *removeMinAndFindNext(Node *p, Node **minNode)
    {
        if (p->Left)
        {
            p->Left = removeMinAndFindNext(p->Left, minNode);
            return balance(p);
        }
        *minNode = p;
        return p->Right;
    }

    Node *remove(Node *&p, const T &key)
    {
        if (!p)
            return nullptr;
        if (cmp(key, p->Key))
            p->Left = remove(p->Left, key);
        else if (cmp(p->Key, key))
            p->Right = remove(p->Right, key);
        else
        {
            Node *q = p->Left;
            Node *r = p->Right;
            delete p;
            if (!r)
                return q;
            Node *minNode;
            auto next = removeMinAndFindNext(r, &minNode);
            minNode->Right = next;
            minNode->Left = q;
            return balance(minNode);
        }
        return balance(p);
    }

    int findKStatistic(Node *p, const T &key)
    {
        if (!p)
            return 0;
        if (p->Key == key)
            return p->Right ? count(p->Right) : 0;
        else if (cmp(p->Key, key))
            return findKStatistic(p->Right, key);
        return findKStatistic(p->Left, key) + p->Count - count(p->Left);
    }
    T findKElement(Node *p, int statistic)
    {
        if (statistic > count(p->Right))
            return findKElement(p->Left, statistic - count(p->Right) - 1);
        else if (statistic < count(p->Right))
            return findKElement(p->Right, statistic);
        return p->Key;
    }
};

struct IntCmp
{
    bool operator()(int l, int r) { return l < r; }
};

int main()
{
    IntCmp cmp;
    AVLtree<int, IntCmp> tree(cmp);
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i)
    {
        int op, num;
        std::cin >> op >> num;
        switch (op)
        {
        case 1:
            tree.Add(num);
            std::cout << tree.FindKStatistic(num) << std::endl;
            break;

        case 2:
            tree.Remove(tree.FindKElement(num));
            break;
        }
    }
    return 0;
}