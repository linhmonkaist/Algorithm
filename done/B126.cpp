#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include<math.h>
using namespace std;

const int MOD= (int) 1e9 + 69;
const long long MODSQUARE = 1ll * MOD * MOD;
const int base= 31;
vector<long long> T;
vector<long long> Pow; 
vector<int> hold; 

long long hashh(int i, int j){
    if (i== 0) return T[j];
    return ( T[j] - T[i-1]*Pow[j-i+1] + MODSQUARE) % MOD;
}

int main()
{
    string s; 
    cin >> s;
    int sz= s.size();
    T.assign(sz, 0);
    T[0]= s[0] - 'a' +1; 
    for (int i=1; i<sz; i++){
        T[i]= (T[i-1]*base + s[i] - 'a' + 1) % MOD; 
    }
    Pow.assign(sz, 0);
    Pow[0]= 1;
    for (int i=1; i<sz; i++){
        Pow[i]= (Pow[i-1] * base) % MOD; 
    }
    int i= 0; 
    int j= sz-1;
    int k=0;
    while (k < sz-1){
        if (hashh(i, i+k) == hashh(j-k,j)) hold.push_back(k+1);
        k++; 
    }
    if (hold.size() == 0) {
        cout << "Just a legend";
        return 0; 
    }

    int low= 0, high= hold.size() -1, mid; 
    while (low <= high) {
        int count= 0;
        mid= (high+ low)/2; 
        k= hold[mid]; //length of the selected prefix
        int hashX= T[k-1];
        for (int i= 1; i< sz- k; i++){
            if (hashX == hashh(i, i+ k-1)) {
                count++; 
            }
        }
        if (count == 1) {
            high= mid; 
            break;
        } 
        if (count > 1) low= mid+1; 
        else high = mid-1; 
    }
    if (high == -1) {
        cout << "Just a legend"; 
        return 0;
    }
    cout << s.substr(0, hold[high]);
    return 0;
}