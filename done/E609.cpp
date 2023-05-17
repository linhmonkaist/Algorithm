#include <bits/stdc++.h>
using namespace std;

int n,m; 
vector<long long> ans; 
vector<int> h;
vector<vector<pair<int, int>>> lcaTable;
vector<vector<pair<int, int>>> vertices; 

struct Edge{
    int u, v, index, w; 
    Edge(int _u, int _v, int _i, int _w) : u(_u), v(_v), index(_i), w(_w){};
};

struct DSU{
    vector<int> lab; 
    DSU(int n){ 
        lab.assign(n+3, -1);
    }
    int find_set(int u){
        return lab[u] < 0? u : lab[u]= find_set(lab[u]); 
    }
    bool join_set(Edge e){
        int u= find_set(e.u);
        int v= find_set(e.v);
        if(u == v) return false; 
        if(lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u; 
        return true; 
    }
};

void dfs(int u, int par, int w){
    h[u] = h[par] + 1; 
    lcaTable[u][0].first= par; 
    lcaTable[u][0].second= w; 
    for (int j=1; (1 << j) < n; j++){
        lcaTable[u][j].first= lcaTable[lcaTable[u][j-1].first][j-1].first;
        lcaTable[u][j].second= max(lcaTable[u][j-1].second, lcaTable[lcaTable[u][j-1].first][j-1].second); 
    }
    for (pair<int, int> &child: vertices[u]){
        if (child.first == par) continue;
        dfs(child.first, u, child.second); 
    }
}

void buildLCA(){
    lcaTable.assign(n+1, vector<pair<int, int>>(log2(n+1) +1));
    h.assign(n+1, 0);
    h[1]= -1; 
    dfs(1, 1, 0); 
}

int findLCA(Edge e){
    int u= e.u, v= e.v, ans= 0;
    if (h[u] < h[v]) swap(u,v);
    for (int i= log2(h[u]); i >= 0; i--){
        if (h[u] - (1 << i) >= h[v]) ans= max(lcaTable[u][i].second, ans), u= lcaTable[u][i].first; 
    }
    if (u == v) return ans; 
    for (int i= log2(h[u]); i >= 0; i--){
        if (lcaTable[u][i].first != lcaTable[v][i].first){
            ans= max({ans, lcaTable[u][i].second, lcaTable[v][i].second}); 
            u= lcaTable[u][i].first;
            v= lcaTable[v][i].first;
        }
    }
    return max({ans, lcaTable[u][0].second, lcaTable[v][0].second}); 
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("test.inp", "r"))
    {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
    cout << log2(-1);
    cin >> n >> m; 
    vector<Edge> edges(m+1, Edge(0,0,0,0)), nonEdges;
    vertices.assign(n+1, vector<pair<int, int>>());
    for (int i=1; i <= m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].index= i;
    }
    sort(edges.begin(), edges.end(), [](Edge &x, Edge &y){
        return x.w < y.w; 
    });
    DSU g(n); 
    long long minW= 0; 
    for (Edge &e: edges){
        bool check= g.join_set(e); 
        if (check){ 
            minW += e.w; 
            vertices[e.u].push_back({e.v, e.w});
            vertices[e.v].push_back({e.u, e.w}); 
        } else {
            nonEdges.push_back(e); 
        }
    }
    ans.assign(m+1, minW); 
    buildLCA();
    for (Edge &e: nonEdges){
        int temp= findLCA(e); 
        // cout << "index "<< e.index << " : "<< temp << "\n";
        ans[e.index]= minW - temp + e.w; 
    }

    for (int i=1; i <= m; i++){
        cout << ans[i] <<'\n';
    }
    return 0;
}