#include <bits/stdc++.h>
using namespace std;

int n; 
vector<vector<int>> s, t; 

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    s.assign(n+1, vector<int>(n+1,0));
    t.assign(n+1, vector<int>(n+1, INT_MAX));
    for (int i = 0; i < n; i++){
        for (int j= 0; j< n; j++){
            cin >> s[i][j]; 
        }
    }
    t[0][0]= 0;
    t[1][0]= s[0][1] *2; 
    for (int i= 1; i< n; i++){
        for (int j= 0; j< i-1; j++){
            t[i][j]= t[i-1][j] + s[i][i-1] + s[0][i] - s[i-1][0]; 
            // cout << t[i][j] << ' '; 
            t[i][i-1]= min(t[i][i-1], t[i-1][j] - s[0][j] + s[j][i] + s[0][i]);
        }
        // cout << t[i][i-1] << '\n'; 
    }
    int min_ans= INT_MAX; 
    for (int i=0; i<n; i++){
        min_ans= min(min_ans, t[n-1][i]); 
    }
    cout << min_ans; 
    
    return 0; 
}