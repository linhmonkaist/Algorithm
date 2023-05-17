#include <bits/stdc++.h>
using namespace std;

int n; 
vector<int> a,b; 

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    a.assign(n,0);
    b.assign(n+1, INT_MIN); 
    for (int i=0; i<n; i++) cin >> a[i];
    b[1]= a[0];
    int ans= 1; 
    for (int i=0; i<n; i++){
        int j= lower_bound(b.begin()+1, b.end(), a[i], greater<int>()) - b.begin();
        // cout << a[i] << ' '<< ' '<< j << '\n'; 
        ans= max(ans, j);
        b[j]= a[i]; 
    }
    cout << ans; 
    return 0; 
}