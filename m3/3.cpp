#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::pair;
using std::make_pair;
using std::priority_queue;

const int INF = std::numeric_limits<int>::max();

class IGraph {
public:
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int cost) = 0;
    virtual int VerticesCount() const = 0;
    virtual vector<pair<int, int>> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int vertexCount) : adjacencyList(vertexCount) {}

    void AddEdge(int from, int to, int cost) override {
        adjacencyList[from].push_back(make_pair(to, cost));
        adjacencyList[to].push_back(make_pair(from, cost));
    }

    int VerticesCount() const override {
        return adjacencyList.size();
    }

    vector<pair<int, int>> GetNextVertices(int vertex) const override {
        return adjacencyList[vertex];
    }

private:
    vector<vector<pair<int, int>>> adjacencyList;
};


vector<int> Dijkstra(const IGraph& graph, int from) {
    vector<int> distances(graph.VerticesCount(), INF);
    distances[from] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
    pq.push(make_pair(0, from));

    while (!pq.empty()) {
        auto [currentDistance, current] = pq.top();
        pq.pop();

        if (currentDistance > distances[current]) {
            continue;
        }

        vector<pair<int, int>> nextVertices = graph.GetNextVertices(current);
        for (const auto& next : nextVertices) {
            int neighbor = next.first;
            int weight = next.second;
            int distance = currentDistance + weight;

            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                pq.push(make_pair(distance, neighbor)); // -- сначала надо удалить старое вхождение
            }
        }
    }

    return distances;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    IGraph* listGraph = new ListGraph(n);

    for (int i = 0; i < k; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        listGraph->AddEdge(from, to, cost);
    }
    int from, to;
    std::cin >> from >> to;

    vector<int> distances = Dijkstra(*listGraph, from);
    int shortestPath = distances[to];

    std::cout << shortestPath << std::endl;

    delete listGraph;
    return 0;
}
