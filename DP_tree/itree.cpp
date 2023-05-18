#include <bits/stdc++.h>
using namespace std;
int t, n; 
const int inf= (int) 1e7; 
vector<int> a; 
typedef pair<int, int> pii; 
vector<vector<pii>> itree;
vector<pii> weight;  
void dfs(int u){
    if (itree[u].size() == 0){
        a[u]= 0; 
        weight[u].second= inf; 
        // cout << "leaf: "<< u << '\n';
        return; 
    }
    for (pii &chld: itree[u]){
        dfs(chld.first); 
        weight[u].first += weight[chld.first].first; 
        weight[u].second += min(weight[chld.first].first + chld.second, 
                                weight[chld.first].second); 
    }
    // cout << u << ' ' << weight[u].first << ' '<< weight[u].second << '\n';
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> t;
    for (int i=0; i< t; i++){
        cin >> n; 
        if (n == 1){
            cout << "0.00\n";
            continue;
        }
        a.clear();
        a.resize(n+1); 
        itree.clear();
        itree.resize(n+1);
        int par, w; 
        for (int i= 2; i< n+1; i++){
            cin >> par >> w; 
            itree[par].push_back({i, w}); 
        }
        a[1]= 1; 
        weight.clear();
        weight.assign(n+1, {0, 0});
        dfs(1);
        cout << weight[1].second << ".00\n"; 
    }
}