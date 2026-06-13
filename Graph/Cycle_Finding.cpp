#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;


void bellmanFord(vector<vector<int>> &edges, vector<int> &parent, vector<long long> &dist, int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (auto &edge : edges)
        {
            int u = edge[0], v = edge[1], c = edge[2];

            if (dist[v] > dist[u] + c)
            {
                dist[v] = dist[u] + c;
                parent[v] = u;
            }
        }
    }


    int temp = -1;
    for (auto &edge : edges)
    {
        int u = edge[0], v = edge[1], c = edge[2];
        if (dist[v] > dist[u] + c)
        {
            parent[v] = u; 
            temp = v;
            break;
        }
    }

    if (temp == -1)
    {
        cout << "NO\n";
        return;
    }

    for (int i = 0; i < n; i++)
    {
        temp = parent[temp];
    }


    vector<int> cycleNodes;
    int curr = temp;
    do
    {
        cycleNodes.push_back(curr);
        curr = parent[curr];
    } while (curr != temp);

    cycleNodes.push_back(temp);


    reverse(cycleNodes.begin(), cycleNodes.end());

    cout << "YES\n";
    for (auto node : cycleNodes)
    {
        cout << node << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<vector<int>> edges;
    vector<int> parent(n + 1, -1);
    
   
    vector<long long> dist(n + 1, 0); 

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }

    bellmanFord(edges, parent, dist, n);

    return 0;
}