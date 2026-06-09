#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cycle_start = -1;
int cycle_end = -1;

bool dfs(vector<vector<int>>& adj, vector<bool>& vis, vector<int>& parent, int node, int p) {
    vis[node] = true;
    parent[node] = p;

    for (int x : adj[node]) {
        if (x == p) continue; 

        if (vis[x]) {
            cycle_start = x;
            cycle_end = node;
            return true;
        }

        if (!vis[x]) {
            if (dfs(adj, vis, parent, x, node)) return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> parent(n + 1, -1);
    vector<bool> vis(n + 1, false);

    bool found_cycle = false;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (dfs(adj, vis, parent, i, -1)) {
                found_cycle = true;
                break;
            }
        }
    }

    if (!found_cycle) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;
    path.push_back(cycle_start);
    
    for (int curr = cycle_end; curr != cycle_start; curr = parent[curr]) {
        path.push_back(curr);
    }
    
    path.push_back(cycle_start); 
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int x : path) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}