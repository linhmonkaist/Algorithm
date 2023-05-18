#include <bits/stdc++.h>
using namespace std;
int k, r, m, n, max_size; 
vector<int> pos0;
typedef pair<int, int> pii; 
struct house{
    int x, y, s; 
};
vector<house> houses; 
struct serve{
    set<int> h; 
    long long ppl= 0;
    void join_set(set<int> &y){
        for(auto &t: y){
            if (h.find(t) == h.end())
                h.insert(t);
        }
    }
    void com(){
        for (auto &t: h){
            ppl += houses[t].s;
        }
    }
}; 
vector<pii> shops; 
vector<vector<serve>> f; 

int find1(int mask){
    int c= 0; 
    pos0.clear(); 
    for (int i=0; i< m; i++){
        if ((mask >> i)& 1) c++; 
        else pos0.push_back(i); 
    }
    return c; 
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.ans", "w", stdout); 
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
    f.assign(max_size, vector<serve>(k+1));
    for (int i= 0; i< m; i++){
        for (int j= 0; j< n; j++){
            if (sqrt(( houses[j].x - shops[i].first) * ( houses[j].x - shops[i].first) + 
                ( houses[j].y - shops[i].second) * ( houses[j].y - shops[i].second)) <= r){
                    f[1 << i][1].h.insert(j); 
                }
        }
    }
    long long ans= 0; 
    for (int mask= 1; mask< max_size; mask++){
        int num1= find1(mask); 
        if (num1 > k) continue;
        if (num1 == k){
            f[mask][k].com(); 
            ans= max(ans, f[mask][k].ppl);
            continue; 
        }
        for (int &j: pos0){
            f[mask ^ (1 << j)][num1 + 1]= f[mask][num1]; 
            f[mask ^ (1 << j)][num1 + 1].join_set(f[1 << j][1].h); 
        }
    }
    cout << ans; 
    return 0; 
}
