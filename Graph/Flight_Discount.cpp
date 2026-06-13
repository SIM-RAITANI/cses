#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


const long long INF = 1e17;

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));


    priority_queue<pair<long long, pair<int, int>>, 
                   vector<pair<long long, pair<int, int>>>, 
                   greater<pair<long long, pair<int, int>>>> pq;

    dist[1][0] = 0;
    pq.push({0, {1, 0}});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        long long d = top.first;
        int u = top.second.first;
        int coupon_used = top.second.second;

        if (d > dist[u][coupon_used]) continue;


        for (auto &edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;


            if (dist[v][coupon_used] > d + w) {
                dist[v][coupon_used] = d + w;
                pq.push({dist[v][coupon_used], {v, coupon_used}});
            }
            if (coupon_used == 0) {
                if (dist[v][1] > d + w / 2) {
                    dist[v][1] = d + w / 2;
                    pq.push({dist[v][1], {v, 1}});
                }
            }
        }
    }

    cout << dist[n][1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}