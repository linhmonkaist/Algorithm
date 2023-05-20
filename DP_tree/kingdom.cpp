#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> v, c; 
const int inf= (int) 1e8 +1;
vector<vector<int>> kingdom, conquer;  
void dfs(int u, int par){
    if (kingdom[u].size() == 1 && u != 1){
        conquer[u][c[u]]= v[u];
        return; 
    }
    conquer[u][c[u]]= v[u];
    for (int &chld: kingdom[u]){
        if (chld == par) continue; 
        dfs(chld, u);
        for (int j= m; j >= c[u]; j--){
            for (int i= 0; i < m+1; i++){
                if (j-i < 0) break;
                conquer[u][j]= max(conquer[u][j], conquer[chld][i] + conquer[u][j - i]); 
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> m; 
    v.assign(n+1, 0);
    c.assign(n+1, 0); 
    kingdom.resize(n+1);
    for (int i= 2; i< n+1; i++){
        cin >> v[i];
    }
    for (int i= 2; i< n+1; i++){
        cin >> c[i];
    }
    int x, y;  
    for (int i= 1; i< n; i++){
        cin >> x >> y; 
        kingdom[x].emplace_back(y);
        kingdom[y].emplace_back(x); 
    }
    conquer.assign(n+1, vector<int>(m+1, -inf));
    dfs(1, 0);
    int max_v= 0; 
    for(int i= 0; i< m+1; i++){
        max_v= max(max_v, conquer[1][i]);
    }
    cout << max_v; 
    return 0; 
}