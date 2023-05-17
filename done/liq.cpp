#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> a, f, b; 

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    a.assign(n, 0);
    f.assign(n, 0);
    b.assign(n+1, INT_MAX);
    for (int i=0; i<n; i++){
        cin >> a[i];
    }
    b[1]= a[0]; 
    int ans= 1; 
    for (int i=1; i<n; i++){
        int begin= 1, end= i; 
        int mid; 
        while (begin <= end){
            mid= (begin + end)/2; 
            if (b[mid] < a[i]) begin= mid + 1; 
            else end= mid -1;
        }
        ans = max(begin, ans);
        b[begin]= a[i];
    }
    cout << ans ; 
    return 0; 
}