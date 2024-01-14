#include <iostream>
#include <string>
#include <unordered_set>

struct Node
{
    std::string product_name;
    int color;
    int size;
    bool operator==(const Node &other) const
    {
        return product_name == other.product_name && color == other.color && size == other.size;
    }
};

struct NodeHash
{
    size_t operator()(const Node &node) const
    {
        return std::hash<std::string>()(node.product_name) ^ std::hash<int>()(node.color) ^ std::hash<int>()(node.size);
    }
};

int main()
{
    std::unordered_set<Node, NodeHash> mySet;

    char op;
    std::string productName;
    int color, size;

    while (std::cin >> op >> productName >> color >> size)
    {
        Node node{productName, color, size};
        switch (op)
        {
        case '+':
            std::cout << (mySet.insert(node).second ? "OK" : "FAIL") << std::endl;
            break;
        case '-':
            std::cout << (mySet.erase(node) == 1 ? "OK" : "FAIL") << std::endl;
            break;
        case '?':
            std::cout << (mySet.find(node) != mySet.end() ? "OK" : "FAIL") << std::endl;
            break;
        }
    }

    return 0;
}
