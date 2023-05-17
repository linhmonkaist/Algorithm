#include <bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int> prtOdd, prtEven;
    DSU(int n): prtOdd(n, -1), prtEven(n, -1);
    void make_set(int v, int status)
    {   
        if (status == 0){
            prtEven[v] = v;
        } else {
            prtOdd[v]= v; 
        }
        return;
    }
    int find_set(int v, int status){
        if (status ==0 ){
            if (-1 == prtEven[v+1]) return v; 
            return find_set(prtEven[v+1], status);
        } else{
            if (-1 == prtOdd[v+1]) return v; 
            return find_set(prtOdd[v+1], status);
        }
    }
    bool join_set(int u, int v, int status){
        int p= 0; 
        while (){
            int eu= find_set(u, 0);
            int ou= find_set(u, 1);
            int ev= find_set(v + 1, 0);
            int ov= find_set(v + 1, 1);  
            if (eu == u && status == 0){
                //join u-v into v+1 -> h in even
                return true; 
            } 
            if (ou == u && status == 1){
                
            }
        }
        int pu= find_set(u, status);
        int pv= find_set(v, status);
        
        parent[u]= v; 
        sz[v] += sz[u];
    }
    bool check(int u, int v, int status){
        int pu= find_set(u, status);
        int nu= find_set(v, !status); 

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
    int n, m, u, v, status; 
    cin >> n >> m; 
    string s; 
    DSU g(n); 
    for (int i=0; i<m; i++){
        cin >> u >> v >> s; 
        if (s == "even"){
            status= 0; 
            g.make_set(u, status);
            g.make_set(v, status);

        } else {
            status= 1; 
            g.make_set(u, status);
            g.make_set(v, status); 
        }
    }
    return 0;
}