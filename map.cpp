#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <utility>
#include <algorithm>


using namespace std;

int INF = numeric_limits<int>::max();

// Function to add an edge between two nodes
void addEdge(vector<vector<pair<int, int>>>& graph, int src, int dest, int weight) {
    graph[src].push_back(make_pair(dest,weight));
    graph[dest].push_back(make_pair(src,weight));

}

// Dijkstra's algorithm to find the shortest fare path
vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start, int destination) {
    int numNodes = graph.size();
    vector<int> distance(numNodes, INF); // Distance from start to each node
    vector<int> parent(numNodes, -1);    // Parent of each node in the shortest path

    // Custom comparator for min heap based on fare
    auto cmp = []( pair<int, int>& a,  pair<int, int>& b) {
        return a.second > b.second;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    pq.push(make_pair(start, 0));
    distance[start] = 0;
    int flag=0;

    while (!pq.empty()) {
        int currNode = pq.top().first;
        int currDist = pq.top().second;
        pq.pop();

        if (currDist > distance[currNode])
            continue;

        if (currNode == destination)
        {
            flag=1; break;
        }

        for (auto neighbor : graph[currNode]) {
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
    if(flag==1){
     cout<<"Least Fare is: Rs."<<distance[destination]<<"\n";
     int current = destination;
     while (current != -1) {
        path.push_back(current);
        current = parent[current];
     }
    reverse(path.begin(), path.end());}

    return path;
}

//remove the avoided road
void rem( vector<vector<pair<int, int>>>& graph, int s, int d) {
    {
        auto it=graph[s].begin();
        for(auto neighbor: graph[s])
        {
            if(neighbor.first==d)
                {graph[s].erase(it);break;}
            it++;
        }
    }
}


// Function to print the map as a graph
void printMap(vector<vector<pair<int, int>>>& graph) {

    int numNodes = graph.size();
    for (int i = 0; i < numNodes; ++i) {

        for (auto neighbor : graph[i]) {
            cout << "City " << i << ": ";
            cout << "<--- Fare =" << neighbor.second << "---->" << neighbor.first <<"\n";
        }
        cout << endl;
    }
}

int main()
{
    int numNodes, numEdges;
    cout<<"-------WELCOME TO PERSONALIZED LOCAL BUS APP--------\n";
    cout<<"Please Enter The Connecting Buses cites and roads"<<"\n";
    cout << "Enter the number of cities in the map: ";
    cin >> numNodes;
    cout << "Enter the number of buses available: ";
    cin >> numEdges;

    vector<vector<pair<int, int>>> graph(numNodes);

    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        cout << "Enter bus " << i + 1 << " (source, destination, Fare in rupees):";
        cin>>src>>dest>>weight;
        addEdge(graph, src, dest, weight);
    }

    printMap(graph);

    int start, destination;
    cout << "Enter the starting city: ";
    cin >> start;
    cout << "Enter the destination city: ";
    cin >> destination;

    vector<int> shortestPath = dijkstra(graph, start, destination);
    if (shortestPath.size()==0){cout<<"No Connecting buses";return(0);}

    cout << "Route with lowest fare";
    for (auto node : shortestPath) {
        cout <<"->" <<node ;
    }
    cout << endl;


    char choice;
    cout << "Do you want to avoid a specific bus? (y/n): ";
    cin >> choice;
    int asr,adest;

    if (choice == 'y' || choice == 'Y') {

        cout << "Enter the bus  you want to avoid:(source,destination) ";
        cin >> asr>>adest;

        rem(graph,asr,adest);
        vector<int> newshortestPath = dijkstra(graph, start, destination);
        if(newshortestPath.size()==0){cout<<"No Alternative Route";return(0);}
        cout << "Route with least Fare: ";
        for (auto node1 : newshortestPath) {
          cout <<"->"<<node1 ;
    }
    cout << endl;


    }

    return 0;
}

