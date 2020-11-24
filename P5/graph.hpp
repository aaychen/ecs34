#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>

#define FAILED_OPEN_MSG "Failed to open file"
#define INVALID_GRAPH_MSG "Invalid graph"

/**
 * Class for an unweighted, directed graph.
 * Can represent an undirected graph too, since an undirected graph can be
 * converted to a directed graph easily.
 * Does not support multi-edges or self loops.
 */
class UnweightedGraph
{
public:

    /**
     * Assumes that the first line of the file contains the number of vertices
     * and that this number is correct. Within the file, each vertex has
     * an implicit ID from 0 to (n - 1), where n is the number of vertices.
     * For example, if there are n = 8 vertices, then the IDs go from 0 to
     * 7 (inclusive), and edges (see next paragraph) that use IDs that
     * are negative or that are at least n should be rejected (see below).
     *
     * Assumes that each line after the first line represents an edge and
     * contains two integers (the first representing which vertex the edge
     * comes from, and the second representing the vertex to which the edge
     * goes).
     *
     * Assumes that the graph has at least one vertex.
     *
     * Raises std::runtime_error exception (see FAILED_OPEN_MSG macro above
     * for the message to use) if cannot open file.
     * Raises std::runtime_error exception (see INVALID_GRAPH_MSG macro)
     * if file has invalid data,
     * i.e. multi-edges, self loops, or an out-of-bounds
     * integer for an edge's start or end (e.g. the edge (0,4) would not
     * work if there are 3 edges).
     */
    UnweightedGraph(const std::string& filename);

    int getNumVertices() const;

    std::vector<std::vector<bool>> getAdjacencyMatrix() const;

    /**
     * Does not assume that the neighbor/adjacency list of each node
     * is sorted. (The autograder will be mindful of this.) In other words,
     * if we view the returned adjacency lists as a 2D array, the values
     * within a given row need not be sorted. However, the rows must be in a
     * set order such that the first row is the neighbor/adjacency list of
     * vertex #0, the second row is the neighbor/adjacency list of vertex #1,
     * and so on.
     */
    std::vector<std::vector<int>> getAdjacencyLists() const;

    /**
     * Returns a BFS ordering of all vertices reachable from the start node.
     * If start is negative or too high, instead returns empty vector.
     */
    std::vector<int> getBFSOrdering(int start) const;

    /**
     * Returns a DFS ordering of all vertices reachable from the start node.
     * If start is negative or too high, instead returns empty vector.
     */
    std::vector<int> getDFSOrdering(int start) const;

    /**
     * Returns an adjacency matrix representing the transitive closure of
     * this graph.
     * See: https://en.wikipedia.org/wiki/Transitive_closure#In_graph_theory
     *
     * Although it contradicts the definition in the above link ("one or more
     * hops"), we will say that a node can reach itself, i.e. the main diagonal
     * of the matrix should be all true.
     */
    std::vector<std::vector<bool>> getTransitiveClosure() const;

private:
    // TODO: Add your member variables here.
    int numVertices;
    std::vector<std::vector<bool>> adjMatrix;
    std::vector<std::vector<int>> adjList;
};

#endif // GRAPH_HPP
