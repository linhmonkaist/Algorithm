#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include<math.h>
#include <map>
using namespace std;

const int base= 31;
const int MOD= (int) 1e9 + 69; 
const long long MODSQ= 1ll * MOD * MOD; 
vector<long long> Pow; 
vector<long long> T[2]; 

long long hashh(int id, int i, int j){
    if (i==0) return T[id][j]; 
    return (T[id][j] - T[id][i-1] * Pow[j-i+1] + MODSQ) % MOD; 
}

int main(){
    if(fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
    int n; 
    string s, r; 
    cin >> n >> s; 
    r = s; 
    reverse( r.begin(), r.end()); 
    Pow.assign(n, 1);
    T[0].assign(n, 0); T[1].assign(n, 0);
    T[0][0]= s[0] - 'a' +1; 
    T[1][0]= r[0] - 'a' +1; 
    for (int i=1; i< n; i++){
        Pow[i]= Pow[i-1] * base % MOD; 
        T[0][i]= (T[0][i-1] * base + s[i] - 'a' +1) % MOD; 
        T[1][i]= (T[1][i-1] * base + r[i] - 'a' +1) % MOD; 
    }
    int ans= 0; 
    int i=0;
    while (i<n){
        int t= (ans+1)/2;
        auto valid = [&](int x, int y, int z, int t) {
            return x >= 0 && y < n && z >= 0 && t < n;
        };
        while (valid(i-t, i+t, n-1-i-t, n-1-i+t) && hashh(0, i-t, i+t) == hashh(1,n-1-i-t, n-1-i+t)){
            t++;
        }
        ans= max(ans, 2*t-1);
        
        t=(ans)/2;
        while (valid(i - t, i+1+t, n - 2 - i - t, n - 1 - i + t) && hashh(0, i-t, i+1+t) == hashh(1,n-2-i-t, n-1-i+t)){
            t++;
        }
        ans= max(ans, 2*t);
        i ++;
    }
    cout << ans; 
    return 0;
}