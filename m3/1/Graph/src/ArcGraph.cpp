#include "ArcGraph.hpp"
#include <cassert>

ArcGraph::ArcGraph(int vertexCount) {}

ArcGraph::ArcGraph(const IGraph& graph) {
    int vertexCount = graph.VerticesCount();
    for (int i = 0; i < vertexCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int j : nextVertices) {
            AddEdge(i, j);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    int vertexCount = VerticesCount();
    assert(from >= 0 && to >= 0);
    edges.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
    int maxVertex = 0;
    for (const auto& edge : edges) {
        maxVertex = std::max(maxVertex, std::max(edge.first, edge.second));
    }
    return maxVertex + 1;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    int vertexCount = VerticesCount();
    assert(vertex >= 0 && vertex < vertexCount);
    for (const auto& edge : edges) {
        if (edge.first == vertex) {
            nextVertices.push_back(edge.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    int vertexCount = VerticesCount();
    assert(vertex >= 0 && vertex < vertexCount);
    for (const auto& edge : edges) {
        if (edge.second == vertex) {
            prevVertices.push_back(edge.first);
        }
    }
    return prevVertices;
}
