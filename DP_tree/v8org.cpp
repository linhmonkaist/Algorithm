#include <bits/stdc++.h>
using namespace std;
int n, k, del; 
vector<vector<int>> tree; 
vector<int> par; 

int dfs(int v){
    if (tree[v].size() == 0) return 1; 
    int num_child= 0;  
    for (int &chld: tree[v]){
        int temp= dfs(chld); 
        if (temp >= k) {
            // cout << chld << ' '; 
            del++;
        } 
        else num_child += temp; 
    }
    if (num_child + 1 >= k){
        // cout << v << ' '; 
        del++; 
        return 0; 
    } 
    return num_child + 1; 
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> k >> n; 
    int temp; 
    tree.assign(n+1, vector<int>());
    par.assign(n+1, -1);  
    for (int i= 2; i< n+1; i++){
        cin >> temp; 
        tree[temp].push_back(i); 
        par[i]= temp; 
    }
    del= 0; 
    temp= dfs(1); 
    if (temp >= k) del++; 
    cout << del; 
    return 0; 
}