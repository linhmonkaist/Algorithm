#include <bits/stdc++.h>
using namespace std;
int n, m, cur_m;
bool cur_status; 
struct edge{
    int chld, a, b; 
    edge(int _c, int _a, int _b): chld(_c), a(_a), b(_b){};
};
vector<vector<edge>> tree;
vector<int> dis, repaired_dis;
void dfs(int u, int par){
    if(tree[u].size() == 1 && u != 1){
        return; 
    }
    for (edge &e: tree[u]){
        if (e.chld == par) continue;
        dfs(e.chld, u); 
        dis[u]= max(dis[u], dis[e.chld] + e.a);
        repaired_dis[u]= max(repaired_dis[u], repaired_dis[e.chld] + e.b); 
    }
}
void trace_back(int u, int par, int max_path){
    if (cur_m < 0) {
        cur_status= false; 
        return; 
    }
    if(tree[u].size() == 1 && u != 1){
        if (cur_m < 0) {
            cur_status= false; 
        }
        return; 
    }
    for (edge &e: tree[u]){
        if (e.chld == par) continue;
        if (dis[e.chld] + e.a > max_path){
            int gap= dis[e.chld] + e.a - max_path; 
            if (gap < e.a - e.b){
                cur_m -= gap;
                trace_back(e.chld, u, max_path - e.a + gap);
            } else {
                cur_m -= e.a - e.b; 
                trace_back(e.chld, u, max_path - e.b);
            } 
        }
    }
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> m;  
    tree.resize(n+1);
    int u, v; 
    edge temp= edge(0, 0, 0);
    for (int i= 0; i< n-1; i++){
        cin >> u >> v >> temp.a >> temp.b;
        temp.chld= v; 
        tree[u].push_back(temp);
        temp.chld= u; 
        tree[v].push_back(temp);
    }
    dis.assign(n+1, 0); 
    repaired_dis.assign(n+1, 0); 
    dfs(1, 0); 
    int begin= repaired_dis[1], end= dis[1], mid;
    while (begin <= end){
        mid= (begin + end) / 2; 
        cur_m= m;
        cur_status= true;
        // cout << end << ' ' << begin << ' ' << mid <<'\n';
        trace_back(1, 0, mid); 
        if (cur_status) end= mid -1;
        else begin= mid +1; 
    }
    cout << end + 1; 
    return 0;
}