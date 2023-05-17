#include <bits/stdc++.h>
using namespace std;
int n; 
int const label_size= 30; 
vector<vector<int>> tree, table;
vector<pair<int, int>> t_min;  
vector<int> color; 
void dfs(int u, int par){
    iota(table[u].begin(), table[u].end(), 0);
    if (tree[u].size() == 1 && u != 1){
        t_min[u].first= 1; 
        t_min[u].second= 2; 
        return; 
    }
    for (int &chld: tree[u]){
        if (chld == par) continue;
        dfs(chld, u); 
        for (int i= 1; i< label_size; i++){
            if (t_min[chld].first == i){
                table[u][i] += table[chld][t_min[chld].second];
            }else{ 
                table[u][i] += table[chld][t_min[chld].first];
            }
        }
    }
    table[u][0]= INT_MAX;
    t_min[u].first= 0; 
    t_min[u].second= 0; 
    for (int i= 1; i< label_size; i++){
        if (table[u][i] <= table[u][t_min[u].first]){
            t_min[u].second= t_min[u].first;
            t_min[u].first= i;  
        } else {
            if (table[u][i] <= table[u][t_min[u].second])
                t_min[u].second= i; 
        }
    }
}
void traceback(int u, int par, int u_label){
    if (tree[u].size() == 1 && u != 1) return; 
    for (int &chld: tree[u]){
        if (chld == par) continue;
        if (t_min[chld].first == u_label) color[chld]= t_min[chld].second; 
        else color[chld]= t_min[chld].first; 
        traceback(chld, u, color[chld]); 
    }
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    int u, v; 
    tree.assign(n+1, vector<int>()); 
    for (int i= 0; i< n-1; i++){
        cin >> u >> v; 
        tree[u].push_back(v);
        tree[v].push_back(u); 
    }
    table.assign(n+1, vector<int>(label_size)); 
    t_min.resize(n+1); 
    color.assign(n+1, 0); 
    dfs(1, 0);
    cout << table[1][t_min[1].first] << '\n';
    color[1]= t_min[1].first; 
    traceback(1, 0, color[1]); 
    for (int i= 1; i< n+1; i++){
        cout << color[i] << '\n';
    }
    return 0; 
}
