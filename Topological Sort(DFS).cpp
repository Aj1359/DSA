#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include<stack>
using namespace std;

void createadj(unordered_map<int, list<int>> &adj, vector<pair<int, int>> &edges) {
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
    
    }
}

void dfs(int node, unordered_map<int, list<int>> &adj, unordered_map<int, bool> &visited, vector<int> &ans,stack<int> &s) {
    visited[node] = 1;
    ans.push_back(node);
    
    for (auto neighbour : adj[node]) {
        if (!visited[neighbour]) {
            dfs(neighbour, adj, visited, ans,s);
        }
    }
    s.push(node);
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
    
    // Create adjacency list
    createadj(adj, edges);
stack<int> s;
    for (int i = 1; i <= n; i++) {
       
        if (!visited[i]) {
            vector<int> ans;
            dfs(i, adj, visited, ans,s);
      
        }
    }
  while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }



    return 0;
}

