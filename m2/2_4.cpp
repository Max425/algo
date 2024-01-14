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
	bool Has(const T &key) const;
	void BfsLevelOrder(void (*visit)(const T &key)) const;

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
    if (node == nullptr) {
        root = new Node(key);
        return;
    }
    Node *parent = nullptr;
    while (true)
    {
        if (node->Key == key) {
            return;
        }
        parent = node;
        node = cmp(key, parent->Key) ? parent->Left : parent->Right;
        if (node == nullptr) {
            if (cmp(key, parent->Key)) {
                parent->Left = new Node(key);
            } else {
                parent->Right = new Node(key);
            }
            break;
        }
    }
}

template <class T, class Compare>
bool BinaryTree<T, Compare>::Has(const T &key) const
{
	Node *node = root;
	while (node)
	{
		if (node->Key == key)
		{
			return true;
		}
		node = cmp(node->Key, key) ? node->Left : node->Left;
	}
	return false;
}

template <class T, class Compare>
void BinaryTree<T, Compare>::BfsLevelOrder(void (*visit)(const T &key)) const
{
	std::queue<Node *> q;
	q.push(root);
	while (!q.empty())
	{
		Node *next = q.front();
		visit(next->Key);
		q.pop();
		if (next->Left)
			q.push(next->Left);
		if (next->Right)
			q.push(next->Right);
	}
}

struct IntCmp
{
	bool operator()(int l, int r) { return l < r; }
};

int main()
{
	IntCmp cmp;
	BinaryTree<int, IntCmp> tree(cmp);
	int count;
	std::cin >> count;
	for (int i = 0; i < count; ++i) {
		int num;
		std::cin >> num;
		tree.Add(num);
	} 
	tree.BfsLevelOrder([](const int &key)
					   { std::cout << key << " "; });
	return 0;
}