#include <iostream>
#include <vector>
#include <queue>


class IGraph {
public:
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(int vertexCount) : adjacencyList(vertexCount) {}

    void AddEdge(int from, int to) override {
        adjacencyList[from].push_back(to);
        adjacencyList[to].push_back(from);
    }

    int VerticesCount() const override {
        return adjacencyList.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> nextVertices;
        for (int v : adjacencyList[vertex]) {
            nextVertices.push_back(v);
        }
        return nextVertices;
    }

private:
    std::vector<std::vector<int>> adjacencyList;
};


int BFS( const IGraph& graph, int from, int to )
{
    std::vector<int> shortestPaths(graph.VerticesCount(), 0);
    std::vector<int> distances(graph.VerticesCount(), -1);

    std::queue<int> bfsQueue;
    bfsQueue.push(from);
    distances[from] = 0;
    shortestPaths[from] = 1;

    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();

        std::vector<int> adjList = graph.GetNextVertices(current);
        for (int i = 0; i < adjList.size(); ++i) {
            int next = adjList[i];
            if (distances[next] == -1) { // Новая вершина
                distances[next] = distances[current] + 1;
                shortestPaths[next] = shortestPaths[current];
                bfsQueue.push(next);
            } else if (distances[next] == distances[current] + 1) { // Существующая вершина на кратчайшем пути
                shortestPaths[next] += shortestPaths[current];
            }
        }
    }

    return shortestPaths[to];
}

int main()
{
	int n, k;
	std::cin >> n >> k;
	IGraph* listGraph = new ListGraph( n );
	
	for (int i = 0; i < k; ++i) {
		int from, to;
		std::cin >> from >> to;
		listGraph->AddEdge(from, to);
	}
	int from, to;
	std:: cin >> from >> to;
	std::cout << BFS( *listGraph, from, to) << std::endl;
    delete listGraph;
	return 0;
}