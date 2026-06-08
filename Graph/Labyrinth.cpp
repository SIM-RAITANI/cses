#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<char> dir = {'L', 'R', 'U', 'D'};
vector<int> dr = {0, 0, -1, 1};
vector<int> dc = {-1, 1, 0, 0};

void findPath(int start_i, int start_j, vector<vector<char>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> path_from(n, vector<int>(m, -1));
    vector<vector<int>> vis(n, vector<int>(m, 0));
    
    queue<pair<int, int>> q;
    q.push({start_i, start_j});
    vis[start_i][start_j] = 1;
    
    int end_i = -1, end_j = -1;

    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        
        if (grid[r][c] == 'B')
        {
            end_i = r;
            end_j = c;
            break; 
        }
        
        for (int j = 0; j < 4; j++)
        {
            int row = r + dr[j];
            int col = c + dc[j];
            
            if (row >= 0 && col >= 0 && row < n && col < m && !vis[row][col] && (grid[row][col] == '.' || grid[row][col] == 'B'))
            {
                q.push({row, col});
                vis[row][col] = 1;
                path_from[row][col] = j; 
            }
        }
    }
    
    if (end_i == -1) 
    {
        cout << "NO" << endl;
        return;
    }

    string ans = "";
    int curr_i = end_i;
    int curr_j = end_j;
    
    while (curr_i != start_i || curr_j != start_j)
    {
        int d_idx = path_from[curr_i][curr_j];
        ans += dir[d_idx];
        curr_i -= dr[d_idx];
        curr_j -= dc[d_idx];
    }
    
    reverse(ans.begin(), ans.end());
    
    cout << "YES" << endl;
    cout << ans.length() << endl;
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<char>> grid(n, vector<char>(m));
    int start_i = -1, start_j = -1;
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                start_i = i;
                start_j = j;
            }
        }
    }
    
    findPath(start_i, start_j, grid);
    return 0;
}