#include <bits/stdc++.h>
using namespace std;
int k, r, m, n, max_size; 
typedef pair<int, int> pii; 
struct house{
    int x, y, s; 
};
vector<house> houses; 
vector<pii> shops; 
vector<bitset<101>> f;

long long comp(bitset<101>& h){
    long long ppl= 0; 
    for (int i=0; i< n; i++){
        if(h.test(i)) ppl += houses[i].s;
    }
    return ppl; 
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> k >> r >> m; 
    shops.resize(m);
    for (int i= 0; i< m; i++){
        cin >> shops[i].first >> shops[i].second;
    }
    cin >> n; 
    houses.resize(n); 
    for (int i= 0; i< n; i++){
        cin >> houses[i].x >> houses[i].y >> houses[i].s; 
    }
    max_size= 1 << m; 
    f.resize(m);
    for (int i= 0; i< m; i++){
        for (int j= 0; j< n; j++){
            if (sqrt(( houses[j].x - shops[i].first) * ( houses[j].x - shops[i].first) + 
                ( houses[j].y - shops[i].second) * ( houses[j].y - shops[i].second)) <= r){
                    f[i].set(j);
                }
        }
    }
    long long ans= 0; 
    for (int i= 1; i< max_size; i++){
        if (__builtin_popcount(i) == k){
            bitset<101> mask;
            for(int j = 0; j < m; ++j) 
                if((i >> j) & 1) mask |= f[j];
            ans= max(ans, comp(mask));
        }   
    }
    cout << ans; 
    return 0; 
}