#include <bits/stdc++.h>
using namespace std;
int n; 
long long ans; 
const int mod= (int) 1e9 + 7; 
const int divmod = 500000004;
typedef pair<int, int> pii;
vector<vector<pii>> mtree; 
vector<long long> weight; 

void dfs(int u, int par){
    if (mtree[u].size() == 1 && u != 1){
        return; 
    }
    for (pii &chld: mtree[u]){
        if (chld.first == par) continue;
        dfs(chld.first, u); 
        weight[u] = (weight[u] +  1ll * (weight[chld.first] )* chld.second % mod) % mod;
    }
    // cout << "weight "<< u << ": "<< weight[u] << '\n'; 
    long long temp= 0; 
    for (pii &chld: mtree[u]){
        if (chld.first == par) continue;
        temp= (temp + (1ll * (1ll * weight[chld.first] * chld.second)% mod)
                * (weight[u] - (weight[chld.first])* chld.second % mod + mod - 1))%mod;
    }
    ans = (ans + weight[u] + temp * divmod % mod + mod - 1) % mod; 
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n;
    mtree.assign(n+1, vector<pii>());
    int u, v, w; 
    for (int i= 0; i< n - 1; i++){
        cin >> u >> v >> w; 
        mtree[u].push_back({v, w});
        mtree[v].push_back({u, w}); 
    }
    weight.assign(n+1, 1); 
    ans= 0; 
    dfs(1, 0); 
    cout << (ans + mod) % mod; 
    return 0;
}