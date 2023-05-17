#include <bits/stdc++.h>
using namespace std; 
int n;
vector<vector<int>> table; 

int gcd(int a, int b){
    if (b>a) swap(a,b);
    while (b != 0){
        a= a%b; 
        swap(a,b); 
    }
    return a;
}

int find(int begin, int end){
    int gap= log2(end - begin + 1); 
    return  gcd(table[end - (1 << gap) + 1][gap], table[begin][gap]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n; 
    vector<int> a(n); 
    for (int i=0; i<n; i++){
        cin >> a[i]; 
    }
    const int colSize= log2(n) +1; 
    table.assign(n, vector<int>(colSize)); 
    for (int i=0; i<n; i++){
        table[i][0]= a[i]; 
    }
    for (int j=1; (1<<j) <= n; j++){
        for (int i=0; i< n + 1 - (1<<j); i++){
            table[i][j]= gcd(table[i][j-1], table[i + (1 << (j-1))][j-1]); 
        }
    }
    int q;
    cin >> q; 
    int temp; 
    map<int, long long> ans; 
    vector<int> hold(q); 
    for(int& x: hold) cin >> x, ans[x] = 0;
    
    for (int i=0; i<n; i++){
        int j= i; 
        while (j < n){
            int d= find(i, j); 
            int t= j; 
            for (int k= log2(n-j); k >= 0; k--){
                if (t + (1<<k) < n+1 && table[t][k] % d == 0){ 
                    t= t + (1<<k) - 1; 
                }
            } 
            if (ans.count(d) !=0) ans[d] += t-j+1; 
            j= ++t; 
        }
    }
    
    for (int i=0; i<q; i++){
        cout<< ans[hold[i]] << "\n";
    }

    return 0; 
}