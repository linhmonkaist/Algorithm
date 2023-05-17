#include <bits/stdc++.h>
using namespace std;


void lca(){
    int n, temp, child; 
    cin >> n; 
    vector<vector<int>> p; 
    vector<int> h;
    vector<int> a[n+1]; 
    vector<bool> root(n+1, true);
    
    h.assign(n+1, 0); 
    p.assign(n+1, vector<int>(log2(n+1) +1, -1)); 
    for (int i=1; i<n+1; i++){
        cin >> temp; 
        a[i].assign(temp, 0); 
        for (int j= 0; j<temp; j++){
            cin >> child; 
            root[child] = false;
            a[i][j]= child; 
            p[child][0]= i; 
        }
    }
    function<void(int, vector<int>*)> dfs = [&](int ver, vector<int>* adj){
        for (int j=1; (1 << j) < n; j++){
            p[ver][j]= p[p[ver][j-1]][j-1]; 
        }
        if (adj[ver].size()==0) return; 
        for (int &t : adj[ver]){
            h[t]= h[ver] +1; 
            dfs(t, adj); 
        }
        return; 
    };

    for(int i = 1; i <= n; ++i) {
        if(root[i]) {
            p[i][0] = i; //????
            dfs(i, a);
            break;
        }
    }

    int q;
    cin >> q;
    int u, v;
    for (int i = 0; i < q; i++)
    {
        cin >> u >> v;
        if (h[u] < h[v])
            swap(u, v);
        for (int j = log2(h[u]); j >= 0; j--)
        {
            if (h[u] - (1 << j) >= h[v]) 
            {
                u = p[u][j];
            }
        }
        if (u == v) {
            cout << u <<"\n";
            continue; 
        }

        for (int j = log2(h[u]); j >= 0; j--)
        {
            if(p[u][j] != p[v][j])
            {
                u = p[u][j];
                v = p[v][j];
            }
        }
        cout << p[u][0] << "\n";
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("input.txt", "r"))
    {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int test; 
    cin >> test;
    for(int i=0; i<test; i++){
        cout << "Case "<< i +1 <<":\n"; 
        lca(); 
    }
    return 0; 
}