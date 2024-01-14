#include "SetGraph.hpp"
#include <cassert>

SetGraph::SetGraph(int vertexCount) : outgoingEdges(vertexCount), incomingEdges(vertexCount) {}

SetGraph::SetGraph(const IGraph& graph) {
    int vertexCount = graph.VerticesCount();
    outgoingEdges.resize(vertexCount);
    incomingEdges.resize(vertexCount);

    for (int i = 0; i < vertexCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int j : nextVertices) {
            AddEdge(i, j);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    int vertexCount = VerticesCount();
    assert(from >= 0 && from < vertexCount && to >= 0 && to < vertexCount);
    outgoingEdges[from].insert(to);
    incomingEdges[to].insert(from);
}

int SetGraph::VerticesCount() const {
    return outgoingEdges.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    int vertexCount = VerticesCount();
    assert(vertex >= 0 && vertex < vertexCount);
    for (int nextVertex : outgoingEdges[vertex]) {
        nextVertices.push_back(nextVertex);
    }

    return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    int vertexCount = VerticesCount();
    assert(vertex >= 0 && vertex < vertexCount);
    for (int prevVertex : incomingEdges[vertex]) {
        prevVertices.push_back(prevVertex);
    }

    return prevVertices;
}
