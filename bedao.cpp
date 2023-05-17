#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> tree; 
vector<int> c; 
vector<set<int>> p; 
void dfs(int u, int par){
    if (tree[u].size() == 1 && u != 1){
        p[u].insert(c[u]);
        return; 
    }
    for (int &chld: tree[u]){
        if (chld == par) continue;
        dfs(chld, u); 
        if (p[chld].size() > 1){
            cout << "NO";
            p[]
            return; 
        }
    } 
}
int main(){
    cin >> n; 
    int u, v; 
    tree.resize(n+1);
    c.resize(n+1);
    for (int i= 0; i< n-1; i++){
        cin >> u >> v; 
        tree[u].push_back(v);
        tree[v].push_back(u); 
    }
    for (int i= 1; i< n+1; i++){
        cin >> c[i];
    }
    p.resize(n+1); 
    dfs(1, 0); 
}