#include <bits/stdc++.h>
using namespace std;

void updt(long long parent, long long child, map<pair<long long, int>, long long> &weight, long long w){
    int even= child%2;
    if (weight.count({parent, even}) == 0) weight[{parent, even}]= w; 
    else weight[{parent, even}] += w; 
}

int Log2(long long x) {
    return 64 - __builtin_clzll(x) - 1;
}

long long aux(long long u, long long v, map<pair<long long, int>, long long> &weight, long long w){
    long long ans= 0; 
    if ((int)Log2(u) < (int) Log2(v)) swap(u, v);
    while ((int) Log2(u) != (int) Log2(v)){
        updt(u/2, u, weight, w); 
        ans += weight[{u/2, u%2}];
        u= u/2; 
    }
    if (u == v) return ans; 
    while (u > 0 && u != v){
        updt(u/2, u, weight, w);
        updt(v/2, v, weight, w);
        ans += weight[{u/2, u%2}]; 
        ans += weight[{v/2, v%2}];
        u= u/2;
        v= v/2;
    }
    return ans; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("test.inp", "r"))
    {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
    int q; 
    cin >> q; 
    int check;
    long long u, v, w; 
    map<pair<long long, int>,long long> weight; 
    w = (int)1e9 - 1;
    for (int i= 0; i<q; i++){
        cin >> check >> u >> v; 
        if (check == 1){
            cin >> w;
            aux(u, v, weight, w);
        } else {
            cout << aux(u, v, weight, 0) << "\n"; 
        }
    }
    return 0; 
}