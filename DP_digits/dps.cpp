#include <bits/stdc++.h>
using namespace std;
int d, total_dg;
const int inf= (int) 1e9 + 7; 
string k;  
vector<vector<vector<int>>> dp; 
vector<int> mod; 
int dps(int pos, int remain, int f){
    if (pos == total_dg){
        if (remain == 0) return 1; 
        return 0;
    }
    if (dp[pos][remain][f] != -1) return dp[pos][remain][f];
    int lim;
    if (f == 0){
        lim= k[pos] - '0';
    } else {
        lim= 9; 
    }
    long long res= 0; 
    for (int dg= 0; dg <= lim; dg++){
        int nf= f; 
        int nremain= (remain + dg) % d; 
        if (f == 0 && dg < lim) nf= 1; 
        int temp= dps(pos + 1, nremain, nf);
        res = (res + temp);
        if(res >= inf) res -= inf; 
    }
    return dp[pos][remain][f]= res; 
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> k >> d; 
    total_dg= k.length(); 
    dp.assign(total_dg + 1, vector<vector<int>>(d, vector<int>(2, -1)));
    mod.assign(total_dg + 1, 1);
    for (int i= 1; i< total_dg + 1; i++){
        mod[i]= (1ll * mod[i-1] * 10) % d; 
    }
    int res= dps(0, 0, 0);
    // for (int i= 0; i< total_dg; i++){
    //     for (int j= 0; j< d; j++){
    //         cout << dp[i][j][0] << ' ' << dp[i][j][1] << '\n';
    //     }
    //     cout << '\n';
    // }
    cout <<( res -1 + inf) % inf; 
    return 0; 
}