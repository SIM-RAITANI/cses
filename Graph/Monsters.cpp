#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
char dir[] = {'U', 'D', 'L', 'R'};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    queue<pair<int, int>> mq;
    vector<vector<int>> monster_time(n, vector<int>(m, INF));
    pair<int, int> start_pos;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                mq.push({i, j});
                monster_time[i][j] = 0;
            } else if (grid[i][j] == 'A') {
                start_pos = {i, j};
            }
        }
    }

    while (!mq.empty()) {
        auto [r, c] = mq.front();
        mq.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#') {
                if (monster_time[nr][nc] > monster_time[r][c] + 1) {
                    monster_time[nr][nc] = monster_time[r][c] + 1;
                    mq.push({nr, nc});
                }
            }
        }
    }

    queue<pair<int, int>> pq;
    vector<vector<int>> p_time(n, vector<int>(m, INF));
    vector<vector<int>> parent_dir(n, vector<int>(m, -1));
    vector<vector<pair<int, int>>> parent_cell(n, vector<pair<int, int>>(m)); // Fixed line

    pq.push(start_pos);
    p_time[start_pos.first][start_pos.second] = 0;

    int escape_r = -1, escape_c = -1;

    while (!pq.empty()) {
        auto [r, c] = pq.front();
        pq.pop();

        if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
            escape_r = r;
            escape_c = c;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#') {
                int next_time = p_time[r][c] + 1;
                if (next_time < monster_time[nr][nc] && p_time[nr][nc] == INF) {
                    p_time[nr][nc] = next_time;
                    parent_dir[nr][nc] = i;
                    parent_cell[nr][nc] = {r, c};
                    pq.push({nr, nc});
                }
            }
        }
    }

    if (escape_r == -1) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    string path = "";
    int curr_r = escape_r;
    int curr_c = escape_c;

    while (curr_r != start_pos.first || curr_c != start_pos.second) {
        int d = parent_dir[curr_r][curr_c];
        path += dir[d];
        auto [pr, pc] = parent_cell[curr_r][curr_c];
        curr_r = pr;
        curr_c = pc;
    }

    reverse(path.begin(), path.end());
    cout << path.length() << "\n";
    cout << path << "\n";

    return 0;
}