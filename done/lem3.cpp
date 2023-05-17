#include <bits/stdc++.h>
using namespace std;
int n, max_mask;  
vector<vector<int>> a, f; 

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    a.assign(n, vector<int>(n, 0)); 
    for (int i= 0; i< n; i++){
        for (int j= 0; j< n; j++){
            cin >> a[i][j];
        }
    }
    max_mask= 1 << n; 
    f.assign(max_mask, vector<int>(n, INT_MAX));
    for (int i= 0; i< n; i++){
        f[0][i]= 0; 
    } 
    for (int i= 1; i< max_mask; i++){
        for (int j= 0; j< n; j++){
            if ((i >> j) & 1){
                int n_mask= i ^ (1 << j); 
                if (n_mask == 0){
                    f[i][j]= 0; 
                    continue;
                }
                for (int k= 0; k< n; k++){
                    if ((n_mask >> k) & 1){
                        f[i][j]= min(f[i][j], f[n_mask][k] + a[j][k]); 
                    }
                }
            }
        }
    }
    // for (int i= 0; i< max_mask; i++){
    //     for (int j= 0; j< n; j++){
    //         cout << f[i][j] << ' ';
    //     }
    //     cout << '\n'; 
    // }
    int ans= INT_MAX; 
    for (int i= 0; i< n; i++){
        ans= min(ans, f[max_mask-1][i]);
    }
    cout << ans; 
    return 0; 
}