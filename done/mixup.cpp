#include <bits/stdc++.h>
using namespace std; 
int n, k, max_size; 
vector<int> s, pos0, pos1;
vector<vector<long long>> f; 

void find_pos(int i){
    pos0.clear();
    pos1.clear();
    for (int j= 0; j< n; j++){
        if ((i >> j) & 1) pos1.push_back(j);
        else pos0.push_back(j); 
    }
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> k; 
    s.resize(n); 
    max_size= 1 << n; 
    for (int i= 0; i< n; i++){
        cin >> s[i];
    }
    f.assign(max_size, vector<long long>(n, 0)); 
    for (int i=0; i< n; i++){
        f[1 << i][i]= 1;
    }
    for (int mask= 1; mask< max_size; mask++){
        find_pos(mask); 
        for (int &j: pos1){
            for (int &x: pos0){
                if (abs(s[j] - s[x]) > k){
                    f[mask ^ (1 << x)][x] += f[mask][j];
                }
            }

        }
    }
    long long ans= 0; 
    for (int i= 0; i< n; i++){ 
        ans += f[max_size -1][i];
    }
    cout << ans; 
    return 0; 
}