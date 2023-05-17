#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int u, v, w; 
    Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w){};
}; 

vector<Edge> edges; 
vector<long long> ans; 

struct DSU{
    vector<int> prt; 
    DSU(int n){
        prt.assign(n+1, -1);
    }
    int find_set(int u){
        return prt[u] < 0 ? u : prt[u] = find_set(prt[u]); 
    }
    void join_set(int u, int v, int w){
        u= find_set(u);
        v= find_set(v);
        if (u == v) 
            return; 
        if (prt[u] > prt[v]) swap(u, v);
        ans[w] += 1ll * prt[u] * prt[v]; 
        prt[u] += prt[v];
        prt[v] = u; 
        return; 
    }
}; 

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("test.inp", "r"))
    {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
    int n,m, u, v, w, q; 
    cin >> n >> m; 
    ans.assign(n+1, 0);
    for (int i=0; i< n-1; i++){
        cin >> u >> v >> w; 
        edges.push_back(Edge(u, v, w)); 
    }
    sort(edges.begin(), edges.end(), [](Edge &x, Edge &y){
        return x.w < y.w; 
    }); 
    DSU g(n); 
    for( Edge &e: edges){
        g.join_set(e.u, e.v, e.w); 
    }

    for (int i=2; i<= n; i++){
        ans[i] += ans[i-1];
    }
    for (int i=0; i<m; i++){
        cin >> q; 
        if (q > n) cout << ans[n] << '\n'; 
        else cout << ans[q] << '\n';
    }
    return 0;
}