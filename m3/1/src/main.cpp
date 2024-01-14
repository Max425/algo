#include <iostream>
#include <vector>
#include <queue>
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "ArcGraph.hpp"

void BFS( const IGraph& graph, int vertex, void (*visit)(int) )
{
	std::vector<bool> visited( graph.VerticesCount(), false );
	std::queue<int> bfsQ;
	bfsQ.push( vertex );
	visited[vertex] = true;
	while( bfsQ.size() > 0 ) {
		int current = bfsQ.front();
		bfsQ.pop();
		visit( current );
		std::vector<int> adjList = graph.GetNextVertices( current );
		for( int i = 0; i < adjList.size(); ++i ) {
			if( !visited[adjList[i]] ) {
				bfsQ.push( adjList[i] );
				visited[adjList[i]] = true;
			}
		}
	}
}

int main()
{
	std::cout << "TEST ListGraph:\n";
	IGraph* listGraph = new ListGraph( 5 );
	listGraph->AddEdge( 1, 2 );
	listGraph->AddEdge( 2, 3 );
	listGraph->AddEdge( 2, 4 );
	listGraph->AddEdge( 4, 3 );
	listGraph->AddEdge( 4, 1 );

	IGraph* newListGraph = new ListGraph( *listGraph );

	BFS( *newListGraph, 4, []( int vertex ) {  std::cout << vertex << " "; } );
	std::cout << "\nКол-во вершин: " << listGraph->VerticesCount() << std::endl;

	delete listGraph;
	// delete newListGraph;

	std::cout << "\n\nTEST MatrixGraph:\n";
	IGraph* matrixGraph = new MatrixGraph( 5 );
	matrixGraph->AddEdge( 1, 2 );
	matrixGraph->AddEdge( 2, 3 );
	matrixGraph->AddEdge( 2, 4 );
	matrixGraph->AddEdge( 4, 3 );
	matrixGraph->AddEdge( 4, 1 );

	IGraph* newMatrixGraph = new MatrixGraph( *newListGraph );

	BFS( *newMatrixGraph, 4, []( int vertex ) {  std::cout << vertex << " "; } );
	std::cout << "\nКол-во вершин: " << newMatrixGraph->VerticesCount() << std::endl;

 	delete newListGraph;
	delete matrixGraph;
	delete newMatrixGraph;

	std::cout << "\n\nTEST SetGraph:\n";
	IGraph* setGraph = new SetGraph( 5 );
	setGraph->AddEdge( 1, 2 );
	setGraph->AddEdge( 2, 3 );
	setGraph->AddEdge( 2, 4 );
	setGraph->AddEdge( 4, 3 );
	setGraph->AddEdge( 4, 1 );

	IGraph* newSetGraph = new SetGraph( *setGraph );

	BFS( *newSetGraph, 4, []( int vertex ) {  std::cout << vertex << " "; } );
	std::cout << "\nКол-во вершин: " << newSetGraph->VerticesCount() << std::endl;

	delete setGraph;
	delete newSetGraph;

	std::cout << "\n\nTEST ArcGraph:\n";
	IGraph* arcGraph = new ArcGraph( 5 );
	arcGraph->AddEdge( 1, 2 );
	arcGraph->AddEdge( 2, 3 );
	arcGraph->AddEdge( 2, 4 );
	arcGraph->AddEdge( 4, 3 );
	arcGraph->AddEdge( 4, 1 );

	IGraph* newArcGraph = new ArcGraph( *arcGraph );

	BFS( *newArcGraph, 4, []( int vertex ) {  std::cout << vertex << " "; } );
	std::cout << "\nКол-во вершин: " << newArcGraph->VerticesCount() << std::endl;

	delete arcGraph;
	delete newArcGraph;

	return 0;
}