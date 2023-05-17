#include <bits/stdc++.h>
using namespace std; 
int m, n, t; 
int max_case; 
vector<vector<int>> match; 
vector<long long> f[2]; 

bool check(int a, int b){
    for (int i= 0; i< m-1; i++){
        if ((a & 3) == 0 && (b & 3) == 0) return false; 
        if ((a & 3) == 3 && (b & 3) == 3) return false; 
        a= a >> 1; 
        b= b >> 1; 
    }
    return true; 
}

void gen(){
    for (int i=0; i < max_case; i++){
        for (int j= i; j< max_case; j++){
            if (check(i,j)){
                match[i].push_back(j);
                if (i != j) match[j].push_back(i); 
            }
        }
    }
}

void cowGirl(int m, int n){
    int cur= 1;
    f[0].assign(max_case, 1);
    f[1].assign(max_case, -1); 
    for (int i=1; i< n; i++){
        for (int j= 0; j< max_case; j++){
            f[cur][j]= 0; 
            for (int &x: match[j]){
                f[cur][j] += f[cur ^ 1][x]; 
            }
        }
        cur= cur ^ 1;
    }
    long long ans= 0; 
    for (int i=0; i< max_case; i++){
        ans += f[cur ^ 1][i]; 
    }
    cout << ans << '\n'; 
    return; 
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> t; 
    for (int i= 0; i< t; i++){
        cin >> m >> n;
        if (m > n) swap(m,n);
        max_case= 1 << m; 
        match.clear();
        match.resize(max_case);
        gen(); 
        cowGirl(m, n); 
    }
    return 0; 
}