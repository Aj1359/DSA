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

bool dfs(int node, unordered_map<int, list<int>> &adj, unordered_map<int, bool> &visited,unordered_map<int,bool> &dfsvisited) {
    visited[node] = 1;
    dfsvisited[node]=1;
    
    for (auto neighbour : adj[node]) {
        if (!visited[neighbour]) {
        bool c=dfs(neighbour, adj, visited, dfsvisited);
        if(c){
            return true;
        }}
        else if(dfsvisited[node]==1){
            return true;
        }
        
    } 
    dfsvisited[node]=0;
    return false;
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
      unordered_map<int, bool> dfsvisited;
    
    // Create adjacency list
    createadj(adj, edges);

int cnt=0;
 
    for (int i = 1; i <= n; i++) {
       
        if (!visited[i]) {
            bool cycle=dfs(i, adj, visited, dfsvisited);
            if(cycle){
                cnt=1;
            }
      
        }
    }

if(cnt==0){
    cout<<"It is valid Directed Acyclic Graph"<<endl;
}else{
    cout<<"It is invalid Directed Acyclic Graph"<<endl;
}


    return 0;
}

