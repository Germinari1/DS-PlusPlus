/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//* Author: Lucas Germinari Carreira
//* Last update date: 04/30/2024
//* Description(data structure implementation): implements a undirected graph data structure using an adjacency list representation (both weighted and unweighted)
//* Tested: yes, passed 
//* Notes:
    - This implementation allows a user to pass a custom function (if not, the default function will be used) to traverse the graph and perform an operation on each node
    - Directed graphs are also supported
    - Djikstra's algorithm: single shortest path; both directed and undirected graphs; finds shortest path from a source node to all other nodes
        - time complexity: O(V"2) -> happens in complete graph
        - might not work with negative weights
    - Minimum Spanning Tree: 
        - Kruskal's algorithm
            - find next min cost edge to add (edge must not create a cycle) => "global view" of graph
        - Prim's algorithm
            - find next min cost edge to add (edge must be conection to current subtree, edge must not create a cycle)
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

//HEADER FILES
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <functional>
#include <unordered_set>
#include <stack>
#include <queue>

template <typename T>
void defaultTraverseFunction(const T& node) {
    std::cout << node << " ";
}

template <typename T, typename Func = std::function<void(const T&)>>
class Graph {
private:
    std::unordered_map<T, std::list<std::pair<T, int>>> adjList;
    bool isWeighted;
    bool isDirected;

    //helper functino for depth first search
    void dfsUtil(const T& vertex, std::unordered_set<T>& visited, Func func) const {
        visited.insert(vertex);
        func(vertex);

        for (const auto& neighbor : adjList.at(vertex)) {
            const T& adjVertex = neighbor.first;
            if (visited.find(adjVertex) == visited.end()) {
                dfsUtil(adjVertex, visited, func);
            }
        }
    }

public:
    Graph(bool weighted = false, bool directed = false) : isWeighted(weighted), isDirected(directed) {}

    void addVertex(const T& vertex) {
        adjList[vertex] = {};
    }

    void addEdge(const T& src, const T& dest, int weight = 1) {
        adjList[src].push_back(std::make_pair(dest, isWeighted ? weight : 1));
        if (!isDirected) {
            adjList[dest].push_back(std::make_pair(src, isWeighted ? weight : 1));
        }
    }

    void removeEdge(const T& src, const T& dest) {
        auto& srcAdjList = adjList[src];
        srcAdjList.remove(std::make_pair(dest, isWeighted ? 0 : 1));
        if (!isDirected) {
            auto& destAdjList = adjList[dest];
            destAdjList.remove(std::make_pair(src, isWeighted ? 0 : 1));
        }
    }

    void printGraph() const {
        for (const auto& pair : adjList) {
            std::cout << pair.first << ": ";
            for (const auto& neighbor : pair.second) {
                std::cout << "(" << neighbor.first;
                if (isWeighted) {
                    std::cout << ", " << neighbor.second << ") ";
                } else {
                    std::cout << ") ";
                }
            }
            std::cout << std::endl;
        }
    }

    void clearGraph() {
        adjList.clear();
    }

    bool isEmpty() const {
        return adjList.empty();
    }

    void traverseGraph(Func func = defaultTraverseFunction<T>) const {
        for (const auto& pair : adjList) {
            func(pair.first);
        }
    }

    //depth first search
    void dfs(const T& startVertex, Func func = defaultTraverseFunction<T>) {
        std::unordered_set<T> visited;
        dfsUtil(startVertex, visited, func);
    }

    void dfs_stack(const T& startVertex, Func func = defaultTraverseFunction<T>) {
        std::unordered_set<T> visited;
        std::stack<T> stack;

        stack.push(startVertex);

        while (!stack.empty()) {
            T currentVertex = stack.top();
            stack.pop();

            if (visited.find(currentVertex) == visited.end()) {
                func(currentVertex);
                visited.insert(currentVertex);

                for (const auto& neighbor : adjList.at(currentVertex)) {
                    const T& adjVertex = neighbor.first;
                    if (visited.find(adjVertex) == visited.end()) {
                        stack.push(adjVertex);
                    }
                }
            }
        }
    }

    //breadth first search
    void bfs_queue(const T& startVertex, Func func = defaultTraverseFunction<T>) {
        std::unordered_set<T> visited;
        std::queue<T> queue;

        visited.insert(startVertex);
        queue.push(startVertex);

        while (!queue.empty()) {
            T currentVertex = queue.front();
            queue.pop();
            func(currentVertex);

            for (const auto& neighbor : adjList.at(currentVertex)) {
                const T& adjVertex = neighbor.first;
                if (visited.find(adjVertex) == visited.end()) {
                    visited.insert(adjVertex);
                    queue.push(adjVertex);
                }
            }
        }
    }

    //find shortes path (dijkstra's algorithm) 
void dijkstra(const T& source, Func func = defaultTraverseFunction<T>) {
        // Create an unordered map to store the shortest distance from the source to each vertex
        std::unordered_map<T, int> distances;

        // Create an unordered map to store the previous vertex in the shortest path
        std::unordered_map<T, T> previousVertices;

        // Create a priority queue to store the vertices along with their distances from the source
        // The priority queue is ordered based on the distances, with smaller distances having higher priority
        std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;

        // Initialize all distances to infinity and previous vertices to source
        for (const auto& vertex : adjList) {
            distances[vertex.first] = std::numeric_limits<int>::max(); // Set distance to infinity
            previousVertices[vertex.first] = source; // Set the previous vertex to the source
        }

        // Distance from the source to itself is 0
        distances[source] = 0;
        pq.push(std::make_pair(0, source)); // Push the source vertex into the priority queue with distance 0

        while (!pq.empty()) {
            // Extract the vertex with the smallest distance from the priority queue
            T currentVertex = pq.top().second;
            pq.pop();

            func(currentVertex); // Perform the operation on the current vertex

            // Visit each neighbor of the current vertex
            for (const auto& neighbor : adjList[currentVertex]) {
                const T& adjVertex = neighbor.first; // Get the adjacent vertex
                int weight = neighbor.second; // Get the weight of the edge

                // If the distance to the neighbor can be shortened by going through the current vertex
                if (distances[adjVertex] > distances[currentVertex] + weight) {
                    // Update the distance to the neighbor
                    distances[adjVertex] = distances[currentVertex] + weight;
                    // Update the previous vertex in the shortest path
                    previousVertices[adjVertex] = currentVertex;
                    // Push the neighbor into the priority queue with its updated distance
                    pq.push(std::make_pair(distances[adjVertex], adjVertex));
                }
            }
        }

        // Print the shortest distances and paths
        for (const auto& vertex : adjList) {
            const T& dest = vertex.first; // Get the destination vertex
            std::cout << "Shortest distance from " << source << " to " << dest << " is " << distances[dest] << std::endl;

            std::cout << "Path: ";
            T currentVertex = dest; // Start from the destination vertex
            std::vector<T> path; // Create a vector to store the path

            // Traverse the path backward from the destination to the source
            while (currentVertex != source) {
                path.push_back(currentVertex); // Add the current vertex to the path
                currentVertex = previousVertices[currentVertex]; // Move to the previous vertex in the path
            }
            path.push_back(source); // Add the source vertex to the path
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order

            // Print the path
            for (const T& v : path) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }
};