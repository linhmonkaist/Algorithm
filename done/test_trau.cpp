#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    if (fopen("test.inp", "r"))
    {
        freopen("test.inp", "r", stdin);
        freopen("test.ans", "w", stdout);
    }
    unordered_map<ll, ll>m;
    int a , q;
    cin >> a;
    while(a--){
    cin >> q;
    ll u , v , w = 0 ;
    q - 2 ? cin >> u >> v >> w : cin >> u >> v ;
    while(u != v){
        if(u < v){
            swap(u,v);
        }
        q - 2 ? m[u] += w : w += m[u];
        u >>= 1;
    }
    q - 2 ? cout : cout << w << endl;
    }
    return 0 ;
}

