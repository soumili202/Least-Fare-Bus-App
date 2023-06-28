#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

// Function to add an edge between two nodes
void addEdge(vector<vector<pair<int, int>>>& graph, int src, int dest, int weight) {
    graph[src].push_back(make_pair(dest, weight));
    graph[dest].push_back(make_pair(src, weight));
}

// Dijkstra's algorithm to find the shortest path
vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start, int destination) {
    int numNodes = graph.size();
    vector<int> distance(numNodes, INF); // Distance from start to each node
    vector<int> parent(numNodes, -1);    // Parent of each node in the shortest path

    // Custom comparator for min heap based on distance
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    pq.push(make_pair(start, 0));
    distance[start] = 0;

    while (!pq.empty()) {
        int currNode = pq.top().first;
        int currDist = pq.top().second;
        pq.pop();

        if (currDist > distance[currNode])
            continue;

        if (currNode == destination)
            break;

        for (const auto& neighbor : graph[currNode]) {
            int neighborId = neighbor.first;
            int edgeWeight = neighbor.second;
            int newDist = currDist + edgeWeight;

            if (newDist < distance[neighborId]) {
                distance[neighborId] = newDist;
                parent[neighborId] = currNode;
                pq.push(make_pair(neighborId, newDist));
            }
        }
    }

    // Reconstruct the shortest path
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());

    return path;
}

// Depth-First Search to find the next shortest path
void dfs(const vector<vector<pair<int, int>>>& graph, int start, int destination, int avoidRoad) {
    vector<bool> visited(graph.size(), false);
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int current = st.top();
        st.pop();

        if (current == destination) {
            cout << "Next Shortest Path: ";
            while (!st.empty()) {
                cout << st.top() << " ";
                st.pop();
            }
            cout << destination << endl;
            return;
        }

        for (const auto& neighbor : graph[current]) {
            int neighborId = neighbor.first;
            int edgeWeight = neighbor.second;

            if (!visited[neighborId] && edgeWeight != INF && edgeWeight != avoidRoad) {
                visited[neighborId] = true;
                st.push(neighborId);
            }
        }
    }

    cout << "No alternative path found." << endl;
}


// Function to print the map as a graph
void printMap(const vector<vector<pair<int, int>>>& graph) {
    int numNodes = graph.size();
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": ";
        for (const auto& neighbor : graph[i]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes in the map: ";
    cin >> numNodes;
    cout << "Enter the number of edges in the map: ";
    cin >> numEdges;

    vector<vector<pair<int, int>>> graph(numNodes);

    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        cout << "Enter edge " << i + 1 << " (source, destination, weight): ";
        cin >> src >> dest >> weight;
        addEdge(graph, src, dest, weight);
    }

    printMap(graph);

    int start, destination;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the destination node: ";
    cin >> destination;

    vector<int> shortestPath = dijkstra(graph, start, destination);

    cout << "Shortest Path: ";
    for (const auto& node : shortestPath) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Shortest Distance: " << shortestPath.size() - 1 << endl;

    char choice;
    cout << "Do you want to avoid a specific road? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int avoidRoad;
        cout << "Enter the road weight you want to avoid: ";
        cin >> avoidRoad;
        dfs(graph, start, destination, avoidRoad);
    }

    return 0;
}
