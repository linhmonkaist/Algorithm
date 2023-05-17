#include <bits/stdc++.h>
using namespace std;

int n, m, q;
vector<pair<int, int>> edges;
vector<int> eli;
vector<bool> check; 

struct DSU{
    vector<int> par; 
    int num_set; 

    DSU(int n){
        par.assign(n+1, -1); 
        num_set= n;
    }
    int find_set(int u){
        return par[u] < 0? u: par[u]= find_set(par[u]); 
    }
    bool join_set(int u, int v){
        u= find_set(u);
        v= find_set(v);
        if (u == v) return false; 
        if (par[u] < par[v]) swap(u, v); 
        par[v] += par[u]; 
        par[u]= v; 
        num_set--; 
        return true; 
    }
};

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> m >> q; 
    edges.assign(m, {0,0});
    eli.assign(q, 0);
    check.assign(m, true); 
    for (int i= 0; i<m; i++) cin >> edges[i].first >> edges[i].second;
    for (int i= 0; i<q; i++) {cin >> eli[i]; check[eli[i]-1]= false;}
    DSU g(n);
    for (int i=0; i < m; i++){
        if (check[i]){
            g.join_set(edges[i].first, edges[i].second);
        }
    }
    vector<int> ans(q, -1); 
    for (int i= q-1; i >= 0; i--){
        int index= eli[i] -1; 
        ans[i]= g.num_set; 
        g.join_set(edges[index].first, edges[index].second); 
    }
    for (int &x: ans){
        cout << x << '\n';
    }
    return 0; 
}