#include <iostream>
#include <queue>

template <class T, class Compare>
class BinaryTree
{
public:
    BinaryTree(const Compare &_cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();
    BinaryTree(const BinaryTree &) = delete;
    BinaryTree &operator=(const BinaryTree &) = delete;

    void Add(const T &key);
    int MinDepth();

private:
    struct Node
    {
        Node *Left;
        Node *Right;
        T Key;
        Node(const T &key) : Left(nullptr), Right(nullptr), Key(key) {}
    };
    Node *root;
    Compare cmp;
    int minDepth(Node *root);
};

template <class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree()
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

template <class T, class Compare>
void BinaryTree<T, Compare>::Add(const T &key)
{
    Node *node = root;
    if (node == nullptr)
    {
        root = new Node(key);
        return;
    }
    Node *parent = nullptr;
    while (true)
    {
        if (node->Key == key)
        {
            return;
        }
        parent = node;
        node = cmp(key, parent->Key) ? parent->Left : parent->Right;
        if (node == nullptr)
        {
            if (cmp(key, parent->Key))
            {
                parent->Left = new Node(key);
            }
            else
            {
                parent->Right = new Node(key);
            }
            break;
        }
    }
}
template <class T, class Compare>
int BinaryTree<T, Compare>::MinDepth()
{
    if (!root)
    {
        return 0;
    }

    std::queue<Node *> q;
    q.push(root);
    int level = 1;

    while (!q.empty())
    {
        int n = q.size();
        for (int i = 0; i < n; i++)
        {
            Node *node = q.front();
            q.pop();
            if (!node->Left && !node->Right)
            {
                return level;
            }
            if (node->Left)
            {
                q.push(node->Left);
            }
            if (node->Right)
            {
                q.push(node->Right);
            }
        }
        level++;
    }
    return level;
}

struct IntCmp
{
    bool operator()(int l, int r) { return l < r; }
};

int main()
{
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);
    int num;
    while (std::cin >> num)
    {
        tree.Add(num);
    }
    std::cout << tree.MinDepth() << std::endl;
    return 0;
}
