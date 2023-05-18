#include <bits/stdc++.h>
using namespace std;
int n, del_chld= -1;
vector<vector<int>> tree; 
vector<int> c, tag, rmv; 
void dfs(int u, int par){
    if (tree[u].size() == 1 && u != 1){
        tag[u]= c[u]; 
        return; 
    }
    int dfr= 0, index= -1;
    for (int &chld: tree[u]){
        if (chld == par) continue;
        dfs(chld, u); 
        if (c[u] != c[chld] && c[u] != -1 && c[chld] != -1){
            dfr += 1;  
            index= chld; 
        }
    } 
    if (dfr > 1 || (dfr == 1 && c[u] != c[par])){
        rmv.push_back(u);
        c[u] = -1; 
    } else if (dfr == 1 && c[u] == c[par]){
        if (del_chld == -1) {
            del_chld= index;
        } 
        rmv.push_back(u);
        c[u]= -1;
    }
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    if (n == 2){
        cout << "YES" << '\n' << 1 << ' '<< 2;
        return 0; 
    }
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
    else if (rmv.size() == 1) {
        cout << "YES" << '\n'; 
        if (del_chld != -1 && rmv[0] > del_chld) cout << del_chld << ' ' << rmv[0];
        else if(del_chld != -1 && rmv[0] < del_chld) cout << rmv[0] << ' ' << del_chld;
        else cout << rmv[0];
    }
    else {
        cout << "YES" << '\n';
        for (int i= 1; i< n+1; i++){
            cout << i << ' '; 
        }
    }
    return 0; 
    
}