#include <bits/stdc++.h>
using namespace std;
 
const int base= 31;
const int MOD= (int) 1e9 + 69; 
const long long MODSQ= 1ll * MOD * MOD; 
vector<long long> Pow; 
vector<long long> T; 
vector<long long> hashSub;
 
long long hashh(int i, int j){
    if (i==0) return T[j]; 
    return (T[j] - T[i-1] * Pow[j-i+1] % MOD + MODSQ) % MOD; 
}
 
int main(){
    string s; 
    int n; 
    cin >> s;
    n= s.size();  
    Pow.assign(n, 1);
    T.assign(n, 0);
    T[0]= s[0] - 'a' +1; 
    for (int i=1; i< n; i++){
        Pow[i]= Pow[i-1] * base % MOD; 
        T[i]= (T[i-1] * base + s[i] - 'a' +1) % MOD; 
    }
    vector<int> prefix; 
    for (int i= 0; i<n; i++){
        if (hashh(0,i) == hashh(n-1-i, n-1)) prefix.push_back(i+1);
    }

    vector<int> temp;
    for (int i= prefix.size()-1; i > 0; i--){
        if (prefix[i] > prefix[i-1] * 2) temp.push_back(prefix[i]);
    }
    temp.push_back(prefix[0]);
    prefix= temp;
    reverse(prefix.begin(), prefix.end());
    for (int& sz: prefix){
        long long hashX= hashh(0, sz-1);
        int standP= sz; 
        int i=0;
        while (i < standP){
            if (hashh(i, i+sz-1) == hashX){
                standP= min(i+ sz+1, n-sz+1); 
            }
            i++; 
        }
        if (i == n-sz+1) {
            cout << sz; 
            return 0;
        }
    }
    return 0; 
}