#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> tree; 
vector<int> c, tag, rmv; 
void dfs(int u, int par){
    if (tree[u].size() == 1 && u != 1){
        tag[u]= c[u]; 
        return; 
    }
    for (int &chld: tree[u]){
        if (chld == par) continue;
        dfs(chld, u); 
        if (c[u] != c[chld] && c[u] != -1 && c[chld] != -1){
            rmv.push_back(u); 
            c[u]= -1; 
        }
    } 
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
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
    tag.assign(n+1, -1); 
    dfs(1, 0); 
    if (rmv.size() > 1) cout << "NO";
    else if (rmv.size() == 1) cout << "YES" << '\n' << rmv[0];
    else {
        cout << "YES" << '\n';
        for (int i= 1; i< n+1; i++){
            cout << i << ' '; 
        }
    }
    return 0; 
    
}