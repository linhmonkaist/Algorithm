#include <bits/stdc++.h>
using namespace std; 

int n, m; 

struct DSU {
    vector<int> prt, cap, ori; 
    DSU(int n){
        prt.assign(n+3, -1);
        cap.assign(n+3, 0); 
        ori.assign(n+3, 0);
    }
    int find_set(int u){
        return prt[u] < 0? u : prt[u]= find_set(prt[u]); 
    }
    void join_set(int u, int w){
        u= find_set(u);
        if (w - ori[u] + cap[u] >= 0)
        {
            w = w - ori[u] + cap[u];
            cap[u] = ori[u];
            
            join_set(u + 1, w);
            prt[u]= find_set(u+1); 
            // cout << "prt[u]: " << prt[u] <<'\n';
        } else {
            cap[u] += w;
        }
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
    cin >> n; 
    DSU g(n);
    for (int i=1; i< n+1; i++){
        cin >> g.ori[i];
    }
    cin >> m; 
    int check, a, w; 
    for (int i=0; i<m; i++){
        cin >> check; 
        if (check == 1){
            cin >> a >> w; 
            g.join_set(a, w);
        } else {
            cin >> a; 
            cout << g.cap[a] << '\n'; 
        }
    }
    return 0; 
}