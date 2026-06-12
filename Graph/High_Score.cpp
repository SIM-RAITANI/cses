#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


const long long INF = 1e17; 

void runBellmanFord(int n, vector<vector<int>> &edges, vector<long long> &dist, vector<int> &corruptedNodes) {
    dist[1] = 0;
    
  
    for (int i = 0; i < n - 1; i++) {
        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            long long wt = edge[2];
            if (dist[u] != INF && dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
            }
        }
    }
    
    for (auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        long long wt = edge[2];
        if (dist[u] != INF && dist[v] > dist[u] + wt) {
            
            corruptedNodes.push_back(v);
        }
    }
}

bool canCorruptionReachTarget(int n, vector<vector<int>> &edges, vector<int> &corruptedNodes) {
    vector<int> vis(n + 1, 0);
    queue<int> q;
    
    for (auto node : corruptedNodes) {
        q.push(node);
        vis[node] = 1;
    }
    

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            if (u == curr && !vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }

    return vis[n] == 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> edges;
    for (int i = 0; i < m; i++) {
        int a, b;
        long long x;
        cin >> a >> b >> x;
        edges.push_back({a, b, (int)(-x)}); 
    }

    vector<long long> dist(n + 1, INF);
    vector<int> corruptedNodes;

   
    runBellmanFord(n, edges, dist, corruptedNodes);

    
    if (dist[n] == INF) {
        return 0;
    }


    if (canCorruptionReachTarget(n, edges, corruptedNodes)) {
        cout << -1 << "\n";
    } else {
        
        cout << dist[n] * (-1) << "\n";
    }

    return 0;
}