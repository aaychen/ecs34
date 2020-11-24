#include "graph.hpp"
#include <fstream>
#include <cstdio>
#include <queue>
#include <stack>

using namespace std;

UnweightedGraph::UnweightedGraph(const std::string& filename)
{
    ifstream file{filename}; // initialize istream to open filename
    if (!file.is_open())
        throw runtime_error{FAILED_OPEN_MSG};
    string buf;
    getline(file, buf);
    numVertices = atoi(buf.c_str());

    // setup adjMatrix
    adjMatrix = std::vector<std::vector<bool>>(numVertices);
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = std::vector<bool>(numVertices, false);
    }
    // setup adjList
    adjList = std::vector<std::vector<int>>(numVertices);

    int id1 = -1, id2 = -1;
    while (getline(file, buf)) {
        sscanf(buf.c_str(), " %d %d ", &id1, &id2); // must convert C++ string to C string to call sscanf()
        if (id1 < 0 || id2 < 0 || id1 >= numVertices || id2 >= numVertices 
                || id1 == id2 || adjMatrix[id1][id2] == 1) { // invalid IDs, self-loop, multi-edges
            throw runtime_error{INVALID_GRAPH_MSG};
        } else {
            adjMatrix[id1][id2] = true;
            adjList[id1].push_back(id2);
        }
    }
    file.close();
}

int UnweightedGraph::getNumVertices() const
{
    return numVertices;
}

std::vector<std::vector<bool>> UnweightedGraph::getAdjacencyMatrix() const
{
    return adjMatrix;
}

std::vector<std::vector<int>> UnweightedGraph::getAdjacencyLists() const
{
    return adjList;
}

std::vector<int> UnweightedGraph::getBFSOrdering(int start) const
{
    vector<int> ordering;
    if (start < 0 || start >= numVertices) return ordering;
    bool disc[numVertices];
    for (int i = 0; i < numVertices; i++) {
        disc[i] = false;
    }
    queue<int> q;
    disc[start] = true;
    q.push(start);
    while (q.size()) {
        int curr = q.front();
        q.pop();
        ordering.push_back(curr);
        for (int neighborID : adjList[curr]) {
            if (!disc[neighborID]) {
                disc[neighborID] = true;
                q.push(neighborID);
            }
        }
    }
    return ordering;
}

std::vector<int> UnweightedGraph::getDFSOrdering(int start) const
{
    vector<int> ordering;
    if (start < 0 || start >= numVertices) return ordering;
    bool processed[numVertices];
    for (int i = 0; i < numVertices; i++) {
        processed[i] = false;
    }
    stack<int> s;
    s.push(start);
    while (s.size()) {
        int curr = s.top();
        s.pop();
        if (!processed[curr]) {
            ordering.push_back(curr);
            processed[curr] = true;
            for (int neighborID : adjList[curr]) {
                if (!processed[neighborID])
                    s.push(neighborID);
            }
        }
    }
    return ordering;
}

std::vector<std::vector<bool>> UnweightedGraph::getTransitiveClosure() const
{
    std::vector<std::vector<bool>> transClosure = adjMatrix;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i == j) 
                transClosure[i][j] = 1;
        }
    }
    for (int i = 0; i < numVertices; i++) {
        vector<int> DFSOrdering = getDFSOrdering(i);
        for (int nodeID : DFSOrdering) {
            if (i != nodeID)
                transClosure[i][nodeID] = 1;
        }
    }
    return transClosure;
}
