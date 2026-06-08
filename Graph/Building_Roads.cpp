#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<set>
using namespace std;
class DSU{
    public:
    vector<int> parent,rank;
    DSU(int n){
        parent.resize(n);
        rank.resize(n,0);
        for (int i=0;i<n;i++){
            parent[i]=i;
        }
    }
    int find(int node){
        if (node == parent[node]) return parent[node];
        return parent[node]=find(parent[node]);
    }
    void unionNode(int u,int v){
        int pu=find(u);
        int pv=find(v);
        if (pu == pv) return ;
        if (rank[pu] > rank[pv]){
            parent[pv]=pu;
        }else if(rank[pv] > rank[pu]){
            parent[pu]=pv;
        }else{
            rank[pu]++;
            parent[pv]=pu;
        }
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin>>n>>m;

    vector<vector<int>> edges;
    DSU ds(n);
    for (int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        edges.push_back({a-1,b-1});
    }
    for (auto edge:edges){
        ds.unionNode(edge[0],edge[1]);
    }
    set<int> st;
    for (int i=0;i<n;i++){
        st.insert(ds.find(i));
    }
    int prev=-1;
    if (st.size() == 1){
        cout << 0 << "\n";
        return 0;
    }
    cout<<st.size()-1<<"\n";
    for (auto j:st){
        if (prev != -1){
           cout<<prev+1<<"\n"<<j+1<<"\n";
        }
        prev=j;
    }
    return 0;
}