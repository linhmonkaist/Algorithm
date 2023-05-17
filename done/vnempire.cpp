#include <bits/stdc++.h>
using namespace std; 

int n; 
struct point{
    int index, x, y, z; 
    // point(int _i, int _x, int _y, int _z): index(_i), x(_x), y(_y), z(_z){};
};

struct edge{
    int u, v, dis; 
    edge(int _u, int _v, int _ux, int _vx): u(_u), v(_v){ dis= abs(_ux - _vx);}; 
};
struct DSU{
    vector<int> par; 
    int num_set, cost; 
    DSU(int n){
        par.assign(n, -1);
        num_set= n; 
        cost= 0; 
    }
    int find_set(int u){
        return par[u] < 0? u: par[u]= find_set(par[u]); 
    }
    void join_set(edge e){
        int u= find_set(e.u);
        int v= find_set(e.v);
        if (u == v) return; 
        if (par[u] < par[v]) swap(u,v);
        par[v] += par[u];
        par[u] = v; 
        num_set--;
        cost += e.dis; 
        return; 
    }
};

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    vector<point> empire(n);
    vector<edge> edges; 
    for (int i=0; i<n; i++){
        empire[i].index= i; 
        cin >> empire[i].x >> empire[i].y >> empire[i].z; 
    }
    sort(empire.begin(), empire.end(), [](point &u, point &v){
        return u.x < v.x; 
    });
    for (int i=1; i<n; i++){
        edges.push_back(edge(empire[i-1].index, empire[i].index, empire[i-1].x, empire[i].x)); 
    }
    sort(empire.begin(), empire.end(), [](point &u, point &v){
        return u.y < v.y; 
    });
    for (int i=1; i<n; i++){
        edges.push_back(edge(empire[i-1].index, empire[i].index, empire[i-1].y, empire[i].y)); 
    }
    sort(empire.begin(), empire.end(), [](point &u, point &v){
        return u.z < v.z; 
    });
    for (int i=1; i<n; i++){
        edges.push_back(edge(empire[i-1].index, empire[i].index, empire[i-1].z, empire[i].z)); 
    }
    sort(edges.begin(), edges.end(), [](edge &x, edge &y){ return x.dis < y.dis;});

    DSU g(n); 
    for (edge &e: edges){
        if (g.num_set == 1) {
            cout << g.cost;
            return 0;
        }
        g.join_set(e); 
    }
    return 0; 
}