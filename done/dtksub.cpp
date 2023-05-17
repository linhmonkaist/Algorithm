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
vector<long long> T; 
vector<long long> hashSub;
 
long long hashh(int i, int j){
    if (i==0) return T[j]; 
    return (T[j] - T[i-1] * Pow[j-i+1] % MOD + MODSQ) % MOD; 
}
 
int main(){
    int n,k; 
    string s; 
    cin >> n >> k >> s; 
    Pow.assign(n, 1);
    T.assign(n, 0);
    T[0]= s[0] - 'a' +1; 
    for (int i=1; i< n; i++){
        Pow[i]= Pow[i-1] * base % MOD; 
        T[i]= (T[i-1] * base + s[i] - 'a' +1) % MOD; 
    }
    int low= 1, high= n-k+1;
    auto check = [&](int mid) {
        for (int i=0; i< n- mid +1; i++){
            hashSub.push_back(hashh(i, i + mid -1)); 
        }
        sort(hashSub.begin(), hashSub.end()); 
        long long hold= hashSub[0];
        int count= 0;
        int maxCount= 0;
        for (long long i: hashSub){
            if (i == hold) {count++;}
            else {
                hold= i;
                maxCount= max(maxCount, count);
                count= 1; 
            }
            // cout << i << " "<< endl; 
        }
        maxCount= max(maxCount, count);
        return maxCount < k;
    };
    int mid;
    while (low <= high){
        hashSub.clear();
        mid= (low+high)/2;
        if (check(mid)) high= mid -1; 
        else low= mid + 1; 
        // cout << "low: "<< low << " high: " << high << endl; 
    }
    cout << high; 
    return 0;
}