#include <bits/stdc++.h>
using namespace std;

int n; 
int const mx_6bit= 1 << 6; 
int const mx_3bit= 1 << 3;
int const max_kn= 300; 
typedef pair<int, int> pii; 
vector<int> keys; 
vector<pii> f[2]; 
vector<vector<int>> table; 
vector<int> z;

bool valid(int i_3bits, int j_6bits, int i){
    bitset<6> bit_6(j_6bits);
    bitset<3> bit_3(i_3bits); 
    if (((bit_6.test(5) || bit_6.test(3)) && bit_3.test(1)) 
        || (bit_6.test(4) && (bit_3.test(2) || bit_3.test(0))) 
        || (bit_6.test(0) && bit_3.test(2)) 
        || (bit_6.test(2) && bit_3.test(0))) 
        return false;
    if ((bit_6.test(5) && bit_6.test(0)) || (bit_6.test(3) && bit_6.test(2))) return false;
    if (i > -1 && z[i] != 0 && bit_3.test(z[i] - 1)) return false;         
    return true; 
}

void gen(){
    keys.clear(); 
    for (int j= 0; j < mx_6bit; j++){
        if (valid(0, j, -1)) keys.push_back(j); 
    }
}
int count(int x){
    return __builtin_popcount(x); 
}
int match(int k_6bit, int j_3bit){
    return(( (k_6bit & 7) << 3) + j_3bit); 
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n; 
    z.assign(n, 0);
    for (int i= 0; i< n; i++){
        cin >> z[i]; 
    }
    if (n==1){
        int c= 0, a= 0; 
        for (int i= 0; i< mx_3bit; i++){
            if(valid(i, 0, 0)){
                if (count(i) > a){
                    a= count(i);
                    c= 1;
                } else if (count(i) == a){
                    c++; 
                }
            }
        }
        cout << a << ' '<< c; 
        return 0;
    }
    gen(); 
    f[0].assign(mx_6bit, {0,0});
    f[1].assign(mx_6bit, {0,0});
    int cur = 1; 
    for (int &k: keys){
        if (z[0] != 0 && (k >> (3+ z[0] - 1) & 1)) continue;
        if (z[1] != 0 && (k >> (z[1] - 1) & 1)) continue; 
        f[0][k].first= count(k);
        f[0][k].second= 1; 
    }
    for (int i= 2; i< n; i++){
        fill(f[cur].begin(), f[cur].end(), pair<int, int>(0,0)); 
        for (int j= 0; j< mx_3bit; j++){
            for (int &k: keys){
                if (!valid(j, k, i)) continue;
                int new_key= match(k, j);
                if (f[cur ^ 1][k].first + count(j) > f[cur][new_key].first){
                    f[cur][new_key].first= f[cur ^ 1][k].first + count(j); 
                    f[cur][new_key].second= f[cur ^ 1][k].second; 
                    continue;
                }
                if (f[cur ^ 1][k].first + count(j) == f[cur][new_key].first){
                    f[cur][new_key].second += f[cur ^1 ][k].second; 
                }
            }
        }
        cur= cur ^ 1; 
    }
    int ans= 0, c= 0; 
    cur= cur ^ 1;
    for (int &k: keys){
        if (f[cur][k].first > ans){
            ans= f[cur][k].first; 
            c= f[cur][k].second;
        } else if (ans == f[cur][k].first){
            c += f[cur][k].second; 
        }
    }
    cout << ans << ' ' << c; 
    return 0; 
}