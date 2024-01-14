#include "MatrixGraph.hpp"
#include <cassert>

MatrixGraph::MatrixGraph(int vertexCount): matrix(vertexCount, std::vector<int>(vertexCount, 0)) {}

MatrixGraph::MatrixGraph(const IGraph &graph)
{
    int vertexCount = graph.VerticesCount();
    matrix.resize(vertexCount, std::vector<int>(vertexCount, 0));

    for (int i = 0; i < vertexCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int j : nextVertices) {
            matrix[i][j] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to)
{
    int vertexCount = VerticesCount();
    assert(from >= 0 && from < vertexCount && to >= 0 && to < vertexCount);
        matrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const
{
    return matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    std::vector<int> nextVertices;
    int vertexCount = VerticesCount();
    assert(vertex >= 0 && vertex < vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        if (matrix[vertex][i] == 1) {
            nextVertices.push_back(i);
        }
    }

    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> prevVertices;
    int vertexCount = VerticesCount();
    assert(vertex >= 0 && vertex < vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        if (matrix[i][vertex] == 1) {
            prevVertices.push_back(i);
        }
    }

    return prevVertices;
}
