#include <bits/stdc++.h>
using namespace std; 
int n, max_size; 
typedef pair<long long, long long> pll; 
vector<vector<int>> a; 
vector<vector<pll>> f; 
vector<int> pos0; 

int find_pos(int i){
    int count= 0; 
    pos0.clear();
    for (int j= 0; j< n; j++){
        if ((i >> j) & 1) count++; 
        else pos0.push_back(j); 
    }
    return count; 
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    max_size= 1 << n; 
    a.assign(n, vector<int>(n)); 
    f.assign(max_size, vector<pll>(n+1, {0,0})); 
    for (int i= 0; i< n; i++){
        for (int j= 0; j< n; j++){
            cin >> a[i][j];
        }
    }
    for (int i=0; i< n; i++){
        f[1 << i][1]= {a[i][0], 1};
    }
    for(int mask=1; mask< max_size; mask++){
        int num1= find_pos(mask); 
        if (num1 >= n) continue;
        for (int &j: pos0){
            if (f[mask ^ (1 << j)][num1 +1].first == f[mask][num1].first + a[j][num1]){
                f[mask ^ (1 << j)][num1 +1].second += f[mask][num1].second;
                continue;
            }
            if (f[mask ^ (1 << j)][num1 +1].first < f[mask][num1].first + a[j][num1]) {
                f[mask ^ (1 << j)][num1 +1].first= f[mask][num1].first + a[j][num1];
                f[mask ^ (1 << j)][num1 +1].second = f[mask][num1].second;
            }
            // cout << (mask ^ (1 << j)) << ' '<< num1+1 << ' '<< f[mask ^ (1 << j)][num1 +1].first << '\n';
        }
    }
    cout << f[max_size -1][n].first << ' '<< f[max_size -1][n].second; 
    return 0; 
}