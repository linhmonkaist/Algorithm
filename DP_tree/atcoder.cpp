#include <bits/stdc++.h>
using namespace std;
int n; 
int const mod= (long long) 1e9 + 7; 
vector<vector<int>> tree;
vector<vector<long long>> color;
void dfs(int u, int par){
    if (tree[u].size() == 1 && u != 1){
        color[u][0]= 1;
        color[u][1]= 1; 
        // cout << u << ' '<< color[u][0] << ' ' << color[u][1] << '\n';
        return; 
    }
    for (int &chld: tree[u]){
        if (chld == par) continue;
        dfs(chld, u); 
        color[u][0] = 1ll * (color[chld][1] + color[chld][0]) * color[u][0] % mod;
        color[u][1] = 1ll * color[chld][0] * color[u][1] % mod; 
    }
    // cout << u << ' '<< color[u][0] << ' ' << color[u][1] << '\n';
    return;
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    int u, v;
    tree.assign(n+1, vector<int>());
    color.assign(n+1, vector<long long>(2, 1)); 
    for (int i= 0; i< n-1; i++){
        cin >> u >> v; 
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    if (n == 1){
        cout << 2;
        return 0; 
    }
    dfs(1, 0);
    cout << (color[1][1] + color[1][0]) % mod; 
    return 0; 
}