#include <bits/stdc++.h>
using namespace std;

int n; 
vector<vector<int>> e; 
typedef pair<int, int> cir; 

cir dfs(int v, int par){
    if (e[v].size() == 1 && e[v][0] == par || e[v].empty()) return {0,0}; 
    int mCir= 0, height = 0; 
    for (int &child: e[v]){
        if(child == par) continue;
        cir temp= dfs(child, v);
        mCir= max({mCir, temp.first, temp.second + height + 1});
        height = max(height, temp.second + 1);  
    }
    return {mCir, height};
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    e.assign(n+1, vector<int>());
    int u, v; 
    for (int i=1; i<n; i++){
        cin >> u >> v; 
        e[u].push_back(v); 
        e[v].push_back(u); 
    }
    cir ans= dfs(1, 0); 
    cout << ans.first  * 3; 
    return 0;
}