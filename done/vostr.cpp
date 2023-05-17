#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include<math.h>
using namespace std;

const int MOD= (int) 1e9 + 69; 
const int base= 31; 
const long long MODSquare= 1ll * MOD * MOD; 
int lenA, lenB;
string a, b;
vector<long long> T[2]; 
vector<long long> Pow; 

void initPow(vector<long long>& Pow){
    Pow.assign(max(lenA, lenB)+2, 1);
    for (int i=1; i < max(lenA, lenB) +2; i++){
        Pow[i]= Pow[i-1] * base % MOD; 
    }
}

long long hashh(int aOrB, int i, int j){
    if (i== 0) return T[aOrB][j];
    return (T[aOrB][j] - T[aOrB][i-1] * Pow[j-i+1] + MODSquare) % MOD; 
}

void printOut(long long a, long long b){
    if (a==b) {
        cout << '='; return;
    }
    if (a < b) { cout << '<'; return;}
    cout << '>';
    return; 
}

void biCheck(int l, int r, int u, int v){
    int minSub= min(r-l, v-u);
    int low= 0, high= minSub;
    while (low <= high){
        int mid= (low + high)/2; 
        if (hashh(0,l, l + mid) == hashh(1,u, u + mid)){
            low= mid+1;
        } else {
            high= mid -1;
        }
    }
    if (high == minSub){
        printOut(r-l, v-u);
        return; 
    }
    printOut(a[l+high+1], b[u+high+1]);
    return; 
}

int main(){ 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int Q; 
    int l,r,u,v; 
    cin >> lenA >> lenB; 
    cin >> a >> b;
    cin >> Q; 

    T[0].assign(lenA+1, 1);
    T[1].assign(lenB+1, 1);
    T[0][0]= a[0] - 'a' +1;
    T[1][0]= b[0] - 'a' +1;
    for (int i= 1; i< lenA; i++){
        T[0][i]= (T[0][i-1] * base + a[i] - 'a' +1) % MOD;
    }
    for (int i= 1; i< lenB; i++){
        T[1][i]= (T[1][i-1] * base + b[i] - 'a' +1) % MOD;
    }
    initPow(Pow);
    for (int i=0; i<Q; i++){
        cin >> l >> r >> u >> v; 
        --l; --r; --u; --v;
        biCheck(l,r,u,v);
    }
    return 0;
}