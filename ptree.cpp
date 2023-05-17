#include <bits/stdc++.h>
using namespace std;
int n, p;
const int inf = (int)2e5 + 1000;
vector<int> c; 
vector<vector<int>> ptree;
vector<int> ans, parent; 
struct itree{
    int value= -inf, child= 0, len= 0; 
}; 
vector<vector<itree>> table;  
void dfs(int u, int par){
    table[u][1].value= c[u];
    if (ptree[u].size() == 1 & u != 1){
        return; 
    }
    for (int &chld: ptree[u]){
        if (chld == par) continue;
        parent[chld] = u; 
        dfs(chld, u);
        for (int i= p; i > 0; i--){
            for (int j= p; j>= 0; j--){
                if (j + i > p) continue;
                if (table[u][i].value + table[chld][j].value > table[u][i+j].value){
                    table[u][i+j].value= table[u][i].value + table[chld][j].value;
                    table[chld][i+j].child= u; 
                    table[chld][i+j].len= j; 
                }
            }
        }
    }
    reverse(ptree[u].begin(), ptree[u].end());
}
void traceback(int u, int sz, int par){
    // cout << "traceback: " << u << ' '<< sz << '\n';
    ans.push_back(u);
    if (sz == 1) return;  
    for (int &chld: ptree[u]){
        if (chld == par) continue;
        if (table[chld][sz].child == u) {
            traceback(chld, table[chld][sz].len, u); 
            sz -= table[chld][sz].len;
        }
    }
    // ans.push_back(table[u][sz- table[u][sz].len].child); 
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> p; 
    c.assign(n+1, 0);
    ptree.resize(n+1);
    int u, v;
    for (int i= 1; i< n+1; i++){
        cin >> c[i];
    }
    for (int i= 0; i< n-1; i++){
        cin >> u >> v; 
        ptree[u].push_back(v);
        ptree[v].push_back(u); 
    }
    table.assign(n+1, vector<itree>(p+1)); 
    parent.assign(n+1, 0); 
    dfs(1, 0); 
    int maxs= 0; 
    for (int i= 1; i< n+1; i++){
        
    }
    int maxV; 
    for (int i= 1; i< n+1; i++){
        // cout << table[i][p].value <<'\n';
        if (table[i][p].value > maxs){
            maxs= table[i][p].value;
            maxV= i; 
        } 
    }
    traceback(maxV, p, parent[maxV]); 
    for (int &u: ans){
        cout << u << ' '; 
    }
    return 0; 
}