#include<iostream>
#include<vector>
#include<queue>
using namespace std;
vector<int> dr={-1,1,0,0};
vector<int> dc={0,0,-1,1};
void bfs(int r,int c,vector<vector<int>> &vis,vector<vector<char>> &nums){
    vis[r][c]=1;
    queue<pair<int,int>> q;
    int n=nums.size(),m=nums[0].size();
    q.push({r,c});
    while(!q.empty()){
        int row=q.front().first;
        int col=q.front().second;
        q.pop();
        for (int i=0;i<4;i++){
            int r=row+dr[i];
            int c=col+dc[i];
            if (r>=0 && r<n && c>=0 && c<m && !vis[r][c] && nums[r][c] == '.'){
                q.push({r,c});
                vis[r][c]=1;
            }
        }
    }

}
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<char>> nums(n,vector<char>(m));
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cin>>nums[i][j];
        }
    }
    vector<vector<int>> vis(n,vector<int>(m,0));
    int count=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            if (nums[i][j] == '.' && !vis[i][j]){
                bfs(i,j,vis,nums);
                count++;
            }
        }
    }
    cout<<count<<endl;
}