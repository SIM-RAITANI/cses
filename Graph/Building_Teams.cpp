#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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

    vector<int> teams(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (teams[i] != 0) continue;

        queue<int> q;
        q.push(i);
        teams[i] = 1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                if (teams[neighbor] == 0) {
                    teams[neighbor] = (teams[curr] == 1) ? 2 : 1;
                    q.push(neighbor);
                } else if (teams[neighbor] == teams[curr]) {
                    cout << "IMPOSSIBLE\n";
                    return 0;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << teams[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}