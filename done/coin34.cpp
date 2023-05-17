#include <bits/stdc++.h>
using namespace std;
int t;
const int sz= 34, half= 17; 
const int M = 1 << half;
typedef pair<int, int> pii;
vector<int> coins; 
vector<pii> f, l; 

int get(int x, int i) {return (x >> i) & 1;}

void gen(vector<pii>& val, int offset){
    for(int cnt, k, i = 0; i < M; ++i) {
        cnt = k = 0;
        for(int j = 0; j < half; ++j) {
            if(get(i, j)) ++cnt, k += coins[offset + j];
        }
        val.emplace_back(k, cnt);
    }
    sort(val.begin(), val.end());
}

int find_min(int x) {
    int p, ans = -1;
    for(auto& u: f) {
        if(u.first > x) return ans;
        if(u.first == x) ans = max(ans, u.second); 
        else {
            p = lower_bound(l.begin(), l.end(), pii(x - u.first + 1, 0)) - l.begin() - 1;
            if(p >= 0 && l[p].first + u.first == x) 
                ans = max(ans, u.second + l[p].second);
        }
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
    coins.assign(sz, 0); 
    coins[0]= 2, coins[1]= 3, coins[2]= 5;
    for (int i= 3; i<sz; i++){
        coins[i]= coins[i-3] + coins[i-2] + coins[i-1]; 
    }
    cin >> t; 
    gen(f, 0);
    gen(l, half);
    int x; 
    for (int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": "; 
        cin >> x;
        cout << find_min(x) <<'\n';
    }
    return 0; 
}