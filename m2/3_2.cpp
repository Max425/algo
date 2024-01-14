#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

template <class T, class Compare>
class BTree
{
public:
	BTree(size_t _t, const Compare &_cmp) : root(nullptr), t(_t), cmp(_cmp) {}
	~BTree() { delete root; }
	BTree(const BTree &) = delete;
	BTree &operator=(const BTree &) = delete;

	void Insert(const T &key);
	void BfsLevelOrder(void (*visit)(const T &key)) const;

private:
	struct Node
	{
		bool IsLeaf;
		std::vector<T> Keys;
		std::vector<Node *> Children;
		Node(bool isLeaf) : IsLeaf(isLeaf) {}
		~Node()
		{
			for (Node *child : Children)
			{
				delete child;
			}
		}
	};
	Node *root;
	size_t t;
	Compare cmp;

	bool isNodeFull(Node *node) const { return node->Keys.size() == 2 * t - 1; }
	void insertNonFull(Node *node, const T &key);
	void splitChild(Node *node, size_t pos);
};

template <class T, class Compare>
void BTree<T, Compare>::Insert(const T &key)
{
	if (root == nullptr)
	{
		root = new Node(true);
	}
	if (isNodeFull(root))
	{
		Node *newRoot = new Node(false);
		newRoot->Children.push_back(root);
		root = newRoot;
		splitChild(root, 0);
	}
	insertNonFull(root, key);
}

template <class T, class Compare>
void BTree<T, Compare>::BfsLevelOrder(void (*visit)(const T &key)) const
{
	std::queue<Node *> q;
	q.push(root);
	while (!q.empty())
	{
		size_t n = q.size();
		for (size_t i = 0; i < n; ++i)
		{
			Node *node = q.front();
			q.pop();
			for (const T &key : node->Keys)
			{
				visit(key);
			}
			if (!node->IsLeaf)
			{
				for (Node *child : node->Children)
				{
					q.push(child);
				}
			}
		}
		std::cout << '\n';
	}
}

template <class T, class Compare>
void BTree<T, Compare>::insertNonFull(Node *node, const T &key)
{
	if (node->IsLeaf)
	{
		auto pos = std::upper_bound(node->Keys.begin(), node->Keys.end(), key, cmp) - node->Keys.begin();
		node->Keys.insert(node->Keys.begin() + pos, key);
	}
	else
	{
		size_t pos = node->Keys.size() - 1;
		while (pos >= 0 && cmp(key, node->Keys[pos]))
		{
			--pos;
		}
		if (isNodeFull(node->Children[pos + 1]))
		{
			splitChild(node, pos + 1);
			if (cmp(node->Keys[pos + 1], key))
			{
				++pos;
			}
		}
		insertNonFull(node->Children[pos + 1], key);
	}
}

template <class T, class Compare>
void BTree<T, Compare>::splitChild(Node *node, size_t pos)
{
	Node *fullChild = node->Children[pos];
	Node *newChild = new Node(fullChild->IsLeaf);
	newChild->Keys.reserve(t - 1);
	newChild->Children.reserve(t);

	newChild->Keys.assign(fullChild->Keys.begin(), fullChild->Keys.begin() + t - 1);
	fullChild->Keys.erase(fullChild->Keys.begin(), fullChild->Keys.begin() + t - 1);
	if (!fullChild->IsLeaf)
	{
		newChild->Children.assign(fullChild->Children.begin(), fullChild->Children.begin() + t);
		fullChild->Children.erase(fullChild->Children.begin(), fullChild->Children.begin() + t);
	}
	node->Children.insert(node->Children.begin() + pos, newChild);

	node->Keys.insert(node->Keys.begin() + pos, fullChild->Keys[0]);
	fullChild->Keys.erase(fullChild->Keys.begin());
}

struct IntCmp
{
	bool operator()(int l, int r) { return l < r; }
};

int main()
{
	int t;
	std::cin >> t;
	IntCmp cmp;
	BTree<int, IntCmp> tree(t, cmp);
	int key;
	while (std::cin >> key)
	{
		tree.Insert(key);
	}
	tree.BfsLevelOrder([](const int &key)
					   { std::cout << key << " "; });
	return 0;
}