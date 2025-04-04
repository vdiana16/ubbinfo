#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

#define INF INT_MAX

struct Edge {
    int source, destination, weight;
};

void addEdge(vector<Edge>& edges, int source, int destination, int weight) {
    edges.push_back({ source, destination, weight });
}

vector<int> Dijkstra(vector<Edge>& edges, int V, int source) {
    vector<int> dist(V, INF);
    dist[source] = 0;

    vector<bool> visited(V, false);

    for (int i = 0; i < V - 1; ++i) {
        int u = -1;
        for (int j = 0; j < V; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (const auto& edge : edges) {
            int v = edge.destination;
            int w = edge.weight;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    return dist;
}

int main() {
    ifstream infile("graf2.txt");
    ofstream outfile("rezultat2.txt");

    int V, E;
    infile >> V >> E;

    vector<Edge> edges;
    for (int i = 0; i < E; ++i) {
        int source, destination, weight;
        infile >> source >> destination >> weight;
        addEdge(edges, source, destination, weight);
    }

    vector<int> distance;
    distance = Dijkstra(edges, V, 0);

    bool hasNegativeCycle = false;
    for (const auto& edge : edges) {
        int u = edge.source;
        int v = edge.destination;
        int w = edge.weight;
        if (distance[u] != INF && distance[u] + w < distance[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        outfile << "-1\n";
        return 0;
    }

    vector<vector<int>> distances(V);
    for (int i = 0; i < V; ++i) {
        distances[i] = Dijkstra(edges, V, i);
    }

    // Output reponderate
    for (const auto& edge : edges) {
        int source = edge.source;
        int destination = edge.destination;
        int weight = edge.weight + distance[source] - distance[destination];
        outfile << source << " " << destination << " " << weight << "\n";
    }

    // Output matrice de distante
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (distances[i][j] == INF) {
                outfile << "INF ";
            }
            else {
                outfile << distances[i][j] + distance[j] - distance[i] << " ";
            }
        }
        outfile << "\n";
    }

    return 0;
}