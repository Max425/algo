#include <iostream>
#include <vector>
#include <string>

struct stringHasher
{
	unsigned int operator()(const std::string &key) const
	{
		unsigned int hash = 0;
		for (unsigned int i = 0; i < key.size(); ++i)
		{
			hash = hash * 137 + key[i];
		}
		return hash;
	}
};

template <class T, class H>
class HashTable
{
public:
	HashTable(int initialSize, const H &hash);
	~HashTable();

	bool Has(const T &key) const;
	bool Add(const T &key);
	bool Delete(const T &key);

private:
	unsigned int secondHasher(const T &key) const;
	void growTable();
	H hasher;
	struct HashTableNode
	{
		T _key;
		enum State
		{
			Empty,
			Key,
			Deleted
		} NodeState;

		HashTableNode() : NodeState(Empty) {}
		HashTableNode(T key) : _key(key), NodeState(Key) {}
	};
	std::vector<HashTableNode> table;
	unsigned int keysCount;
	unsigned int delCount;
};

template <class T, class H>
HashTable<T, H>::HashTable(int initialSize, const H &hash) : hasher(hash),
															 table(initialSize, HashTableNode{}),
															 keysCount(0)
{
}

template <class T, class H>
HashTable<T, H>::~HashTable() {}

template <class T, class H>
bool HashTable<T, H>::Has(const T &key) const
{
	unsigned int hash = hasher(key);
	unsigned int secondHash = secondHasher(key);
	while (table[hash % table.size()].NodeState == HashTableNode::State::Deleted ||
		   (table[hash % table.size()].NodeState == HashTableNode::State::Key && table[hash % table.size()]._key != key))
	{
		hash += secondHash;
	}
	return table[hash % table.size()].NodeState != HashTableNode::State::Empty;
}

template <class T, class H>
bool HashTable<T, H>::Add(const T &key)
{
	if (keysCount > 0.7 * table.size())
		growTable();

	int firstDeleted = -1;
	unsigned int hash = hasher(key);
	unsigned int secondHash = secondHasher(key);
	while (table[hash % table.size()].NodeState == HashTableNode::State::Deleted ||
		   (table[hash % table.size()].NodeState == HashTableNode::State::Key && table[hash % table.size()]._key != key))
	{
		hash += secondHash;
		if (firstDeleted == -1 && table[hash % table.size()].NodeState == HashTableNode::State::Deleted)
			firstDeleted = hash % table.size();
	}
	if (table[hash % table.size()].NodeState != HashTableNode::State::Empty)
		return false;

	++keysCount;
	table[firstDeleted == -1 ? (hash % table.size()) : firstDeleted] = HashTableNode{key};
	return true;
}

template <class T, class H>
bool HashTable<T, H>::Delete(const T &key)
{
	unsigned int hash = hasher(key);
	unsigned int secondHash = secondHasher(key);
	while (table[hash % table.size()].NodeState == HashTableNode::State::Deleted ||
		   (table[hash % table.size()].NodeState == HashTableNode::State::Key && table[hash % table.size()]._key != key))
	{
		hash += secondHash;
	}
	if (table[hash % table.size()].NodeState == HashTableNode::State::Empty)
		return false;
	else
	{
		table[hash % table.size()].NodeState = HashTableNode::State::Deleted;
		++delCount;
		return true;
	}
}

template <class T, class H>
void HashTable<T, H>::growTable()
{
	keysCount = 0;
	int coef = table.size() / delCount >= 1 / 3 ? 2 : 1;
	std::vector<HashTableNode> newTable(table.size() * coef, HashTableNode{});
	for (int i = 0; i < table.size(); ++i)
	{
		if (table[i].NodeState != HashTableNode::State::Key)
			continue;
		unsigned int hash = hasher(table[i]._key);
		unsigned int secondHash = secondHasher(table[i]._key);
		while (newTable[hash % newTable.size()].NodeState != HashTableNode::State::Empty)
		{
			hash += secondHash;
		}
		newTable[hash % newTable.size()] = table[i];
		++keysCount;
	}
	table = newTable;
}

template <class T, class H>
unsigned int HashTable<T, H>::secondHasher(const T &key) const
{
	return hasher(key) * 2 + 1;
}

int main()
{
	stringHasher h;
	HashTable<std::string, stringHasher> table(4, h);
	char operation = 0;
	std::string word;
	while (std::cin >> operation >> word)
	{
		switch (operation)
		{
		case '+':
			std::cout << (table.Add(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			std::cout << (table.Has(word) ? "OK" : "FAIL") << std::endl;
			break;
		}
	}
	return 0;
}