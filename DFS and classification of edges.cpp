#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

void createadj(unordered_map<int, list<int>> &adj, vector<pair<int, int>> &edges) {
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int node, unordered_map<int, list<int>> &adj, unordered_map<int, bool> &visited, vector<int> &ans,unordered_map<int, int> &entrytime,unordered_map<int, int> &exittime,int timer) {
    visited[node] = 1;
    ans.push_back(node);
    timer=timer+1;
    entrytime[node]=timer;
    
    for (auto neighbour : adj[node]) {
        if (!visited[neighbour]) {
            dfs(neighbour, adj, visited, ans,entrytime,exittime,timer);
        }
    }
    timer=timer+1;
    exittime[node]=timer;
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    cout << "Enter the edges (u, v):" << endl;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    unordered_map<int, list<int>> adj;
    unordered_map<int, bool> visited;
    unordered_map<int, int> entrytime;  // To store entry time of each node
    unordered_map<int, int> exittime;   // To store exit time of each node
    int timer = 0;  // Time counter for DFS

    // Initialize entry and exit times
    for (int i = 1; i <= n; i++) {
        entrytime[i] = -1;
        exittime[i] = -1;
    }
    
    // Create adjacency list
    createadj(adj, edges);

 vector<vector<int>> comp;
    for (int i = 1; i <= n; i++) {
       
        if (!visited[i]) {
            vector<int> ans;
            dfs(i, adj, visited, ans,entrytime,exittime,timer);
           comp.push_back(ans);
        }
    }
    for (int i = 0; i < comp.size(); i++) {
        cout << "DFS traversal starting from node " << comp[i][0] << " is: ";
        for (int j = 0; j < comp[i].size(); j++) {
            cout << comp[i][j] << " ";
        }
        cout << endl;
    }
    vector<pair<int, int>> tree, back, forward, cross;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        // Classify based on entry and exit times
        if (entrytime[u] < entrytime[v] && exittime[u] > exittime[v]) {
            tree.push_back({u, v});  // Tree edge
        } else if (entrytime[u] > entrytime[v] && exittime[u] < exittime[v]) {
            back.push_back({u, v});  // Back edge
        } else if (entrytime[u] < entrytime[v] && exittime[u] < exittime[v]) {
            forward.push_back({u, v});  // Forward edge
        } else {
            cross.push_back({u, v});  // Cross edge
        }
    }

    cout << "\nTree Edges: " << endl;
    for (auto &edge : tree) {
        cout << edge.first << " -> " << edge.second << endl;
    }

    cout << "\nBack Edges: " << endl;
    for (auto &edge : back) {
        cout << edge.first << " -> " << edge.second << endl;
    }

    cout << "\nForward Edges: " << endl;
    for (auto &edge : forward) {
        cout << edge.first << " -> " << edge.second << endl;
    }

    cout << "\nCross Edges: " << endl;
    for (auto &edge : cross) {
        cout << edge.first << " -> " << edge.second << endl;
    }

    return 0;
}

