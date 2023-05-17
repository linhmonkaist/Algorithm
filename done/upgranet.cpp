#include <bits/stdc++.h>
using namespace std;

vector<int> h;
vector<vector<pair<int, int>>> lcaTable; 
int n; 

struct Edge{
    int u, v, w; 
    Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w){}; 
};
vector<Edge> grph, out;
vector<vector<pair<int, int>>> edges; 

struct DSU{
    vector<int> lab;
    DSU(int n){
        lab.assign(n+1, -1);
    }

    int find_set(int u){
        return lab[u] < 0? u: lab[u] = find_set(lab[u]);
    }

    bool join_set(int u, int v){
        u= find_set(u);
        v= find_set(v);
        if (u == v) return false; 
        if(lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v], lab[v] = u;
        return true; 
    }
};

void dfs(int u, int par, int w){
    h[u]= h[par] + 1;
    lcaTable[u][0].first= par; 
    lcaTable[u][0].second= w; 
    for(auto &e: edges[u]){
        if(e.first == par) continue;
        dfs(e.first, u, e.second); 
    }
}

void LCAtree(){
    for (int j=1; (1 << j) < n; j++){
        for (int i=1; i < n+1; i++){
            lcaTable[i][j].first= lcaTable[lcaTable[i][j-1].first][j-1].first; 
            lcaTable[i][j].second= min(lcaTable[i][j-1].second, lcaTable[lcaTable[i][j-1].first][j-1].second); 
        }
    }
}

int find_lca(int u, int v){
    int ans= INT_MAX; 
    if (h[u] < h[v]) swap(u,v); 
    for (int i= log2(h[u]); i >= 0; i--){
        if (h[u] - (1 << i) >= h[v]) {
            ans= min(ans, lcaTable[u][i].second);
            u= lcaTable[u][i].first;  
        }
    }
    if (u == v) return ans;
    for (int i= log2(h[u]); i >= 0; i--){
        if (lcaTable[u][i].first != lcaTable[v][i].first){
            ans= min({ans, lcaTable[u][i].second, lcaTable[v][i].second});
            u= lcaTable[u][i].first;
            v= lcaTable[v][i].first;
        }
    }
    ans= min({ans, lcaTable[u][0].second, lcaTable[v][0].second}); 
    return ans; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("test.inp", "r"))
    {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
    int m, u, v, w; 
    cin >> n >> m; 
    h.assign(n+1, 0); lcaTable.assign(n+1, vector<pair<int, int>>(log2(n+1)+1)); 
    for (int i=0; i<m; i++){
        cin >> u >> v >> w; 
        grph.push_back(Edge(u, v, w));
    }
    DSU g(n); 

    sort(grph.begin(), grph.end(), [](Edge &x, Edge &y){
        return x.w > y.w; 
    });
    edges.assign(n+1, vector<pair<int, int>>()); 
    for (Edge &e: grph){
        bool check= g.join_set(e.u, e.v); 
        if (!check){
            out.push_back(e); 
        } else{
            edges[e.u].push_back({e.v, e.w});
            edges[e.v].push_back({e.u, e.w}); 
        }
    }
    h[1]= -1; 
    dfs(1, 1, 0); 

    LCAtree(); 
    int throughput;
    long long d=0;  
    for (Edge &e: out){
        throughput= find_lca(e.u, e.v);
        d += throughput > e.w ? throughput - e.w : 0; 
    }
    cout << d; 
    return 0; 
}