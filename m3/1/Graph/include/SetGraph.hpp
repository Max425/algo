#pragma once
#include "IGraph.hpp"
#include <unordered_set>
#include <unordered_map>

class SetGraph : public IGraph {
public:
	SetGraph( int vertexCount );
	SetGraph( const IGraph& graph );

	// IGraph
	virtual void AddEdge( int from, int to ) override;
	virtual int VerticesCount() const override;
	virtual std::vector<int> GetNextVertices( int vertex ) const override;
	virtual std::vector<int> GetPrevVertices( int vertex ) const override;

private:
    std::vector<std::unordered_set<int>> outgoingEdges;
    std::vector<std::unordered_set<int>> incomingEdges;
};
