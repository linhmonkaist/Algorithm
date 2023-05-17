#include <bits/stdc++.h>
using namespace std; 
int n; 
vector<vector<int>> tree; 
vector<int> need; 
void dfs(int u){
    if (tree[u].size()== 0){
        need[u]= 1;  
        return; 
    }
    for (int &chld: tree[u]){
        dfs(chld); 
    }
    sort(tree[u].begin(), tree[u].end(), [](int &a, int &b){
        return need[a] > need[b]; 
    });
    int temp= 0, needed= 0;
    for (int &chld: tree[u]){
        // cout << u << " is par of " << chld << ": "<< need[chld] << '\n'; 
        temp = temp - need[chld]; 
        if (temp < 0){
            needed -= temp;
            temp= 0; 
        }
        temp= temp + need[chld] - 1; 
    }
    // cout << "need "<< u <<' ' <<needed << '\n';
    need[u]= needed; 
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    tree.resize(n+1); 
    need.resize(n+1);
    int cnt= 1; 
    int par, num_chld; 
    while (cnt < n-1){
        cin >> par >> num_chld; 
        cnt += num_chld; 
        // children[par]= num_chld;
        tree[par].resize(num_chld);
        for (int i= 0; i< num_chld; i++){
            cin >> tree[par][i]; 
        }
    } 
    dfs(1); 
    cout << need[1]; 
    return 0; 
}