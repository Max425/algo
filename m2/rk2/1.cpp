#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

template <class T, class Compare>
class BinaryTree
{
public:
    BinaryTree(const Compare &_cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();
    BinaryTree(const BinaryTree &) = delete;
    BinaryTree &operator=(const BinaryTree &) = delete;

    void Add(const T &key);
    int CheckNodes();

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
int BinaryTree<T, Compare>::CheckNodes()
{
    if (!root)
    {
        return 1;
    }

    std::queue<Node *> q;
    std::vector<T> keys;
    q.push(root);

    while (!q.empty())
    {
        int n = q.size();
        for (int i = 0; i < n; i++)
        {
            Node *node = q.front();
            q.pop();
            if (node->Left)
            {
                q.push(node->Left);
                if (std::find(keys.begin(), keys.end(), node->Right->Key) == keys.end())
                    return 0;
                keys.push_back(node->Left->Key);
            }
            if (node->Right)
            {
                q.push(node->Right);
                if (std::find(keys.begin(), keys.end(), node->Right->Key) == keys.end())
                    return 0;
                keys.push_back(node->Right->Key);
            }
        }
    }
    return 1;
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
    std::cout << tree.CheckNodes() << std::endl;
    return 0;
}
