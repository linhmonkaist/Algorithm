#include <bits/stdc++.h>
using namespace std;
int n, x, sum_weight, max_per;
typedef pair<int, int> pii;
vector<vector<pii>> tree;
vector<int> f;
void dfs(int u, int par){
    if (tree[u].size() == 1 && u != x){
        f[u]= 0; 
        return; 
    }
    int sz= tree[u].size(); 
    for (int i= 0; i< sz; i++){
        if (tree[u][i].first == par) continue;
        dfs(tree[u][i].first, u); 
        f[u]= max(f[u], f[tree[u][i].first] + tree[u][i].second);
    }
    for (int i= 0; i< sz; i++){
        if (tree[u][i].first == par) continue;
        for (int j= i+1; j< sz; j++){
            if (tree[u][j].first == par) continue;
            int temp= tree[u][j].second + tree[u][i].second + f[tree[u][i].first] + f[tree[u][j].first];
            max_per= max(temp, max_per); 
        }
    }

}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> x;
    int u, v, t;
    tree.resize(n+1);
    sum_weight= 0;
    for (int i= 0; i< n-1; i++){
        cin >> u >> v >> t; 
        tree[u].push_back({v, t});
        tree[v].push_back({u, t});
        sum_weight += t; 
    }
    f.resize(n+1); 
    max_per= 0; 
    dfs(x, 0);
    if (max_per == 0) max_per= f[x]; 
    cout << sum_weight * 2 - max_per; 
    return 0;
}