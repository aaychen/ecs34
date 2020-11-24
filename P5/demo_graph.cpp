#include "graph.hpp"

#include <iostream>
#include <vector>

void printAdjMatrix(const std::vector<std::vector<bool>>& matrix)
{
    for (auto row : matrix)
    {
        for (bool val : row)
            std::cout << val << ' ';
        std::cout << '\n';
    }
}

void printGraphInfo(const UnweightedGraph& graph)
{
    std::cout << "Number of vertices: " << graph.getNumVertices() << '\n';
    std::cout << "Adjacency matrix:\n";
    auto adjMatrix = graph.getAdjacencyMatrix();
    printAdjMatrix(adjMatrix);
    std::cout << "Adjacency lists:\n";
    auto adjLists = graph.getAdjacencyLists();
    for (unsigned i = 0; i < adjLists.size(); ++i)
    {
        std::cout << "Vertex #" << i << ": ";
        for (int neighbor : adjLists[i])
            std::cout << neighbor << ' ';
        std::cout << '\n';
    }
    std::cout << "One BFS ordering (many are possible), starting at 0:\n";
    std::vector<int> ordering = graph.getBFSOrdering(0);
    for (int v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "Another BFS ordering, starting at 2:\n";
    ordering = graph.getBFSOrdering(2);
    for (int v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "One DFS ordering, starting at 3:\n";
    ordering = graph.getDFSOrdering(3);
    for (int v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "Transitive closure:\n";
    auto tc = graph.getTransitiveClosure();
    printAdjMatrix(tc);
}

/**
 * Notice that argv is an array of character pointers, even in C++.
 * Although C++ has strings, because C++ is for the most part a superset of C,
 * C++ is stuck with many aspects of C that it cannot change, and this means
 * that you will from time to time encounter scenarios in which you must
 * deal with "C-style strings".
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "No graph files provided.\n";
        return 1;
    }
    std::string filename1 = argv[1];
    UnweightedGraph graph = UnweightedGraph(filename1);
    std::cout << "=== " << filename1 << " ===\n";
    printGraphInfo(graph);
}
