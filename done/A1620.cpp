#include <bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int> parent, sz; 
    DSU(int n): parent(n+1), sz(n+1) {};
    void make_set(int v){
        parent[v]= v;
        sz[v]= 1;  
        return;
    }
    int find_set(int v){
        if (v == parent[v]) return v;
        return find_set(parent[v]); 
    }
    void join_set(int u, int v){
        u= find_set(u);
        v= find_set(v);
        if (sz[u] > sz[v]) swap(u,v);
        parent[u]= v; 
        sz[v] += sz[u];
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
    int t;
    string s;
    cin >> t; 
    int e= -1, n= -1; 
    for (int k=0; k<t; k++){
        cin >> s; 
        int sz= s.length(); 
        int cur= 1;
        DSU d(sz); 
        for (int i=0; i<sz; i++){
            d.make_set(i); 
            if (s[i] == 'E'){
                d.join_set(i, 1); 
                
            }
            if (s[i] == 'N' && n == -1) n= i; 
        }
        for (int i=0; i<sz-1; i++){
            if(s[i] == 'E'){
                d.join_set(i, e); 
                d.join_set(i+1, e);
            } else {
                d.join_set(i, n);
                d.join_set(i+1, e); 
            }
        }
        int i= sz -1; 
        if ((s[i] == 'N' && d.find_set(i) == d.find_set(0)) || (s[i] == 'E' && d.find_set(i) != d.find_set(0))) {
            cout << "NO" << '\n';
        } else {
            cout << "YES" << '\n';
        }
    }
    return 0;
}