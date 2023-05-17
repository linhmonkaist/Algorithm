#include <bits/stdc++.h>
using namespace std;

int n; 
const int plen= 61; 
vector<vector<vector<int>>> table; 
vector<int> prm; 

vector<int> lcmFactor(vector<int> &a, vector<int> &b){
    vector<int> ans(plen, 0);
    for (int i=2; i<plen; i++){
        ans[i]= max(a[i], b[i]); 
    }
    return ans; 
}

vector<int> minFactor(vector<int> &a, vector<int> &b){
    long long fa= 1, fb= 1; 
    for (int &i: prm){
        if (a[i] != 0){
            fa= fa * log(i) * a[i]; 
        }
        if (b[i] != 0){
            fb= fb * log(i) * b[i]; 
        }
    }
    if (fa < fb) return a; 
    return b; 
}

void prime(vector<int> &prime){
    vector<bool> temp(plen, true);
    for (int i=2; i<plen; i++){
        if (!temp[i]) continue;
        for (int j= 2; j*i < plen; j++){
            temp[i*j]= false; 
        }
    }
    for (int i=2; i<plen; i++){
        if (temp[i]) prime.push_back(i);
    }
    return; 
}

vector<int> factor(int a){
    vector<int> ans(plen, 0);
    for (int &p: prm){
        while(a % p == 0){
            ans[p] ++; 
            a= a/p; 
        }
    }
    return ans; 
}

bool checkFactor(vector<int> &a, vector<int> &b){
    for (int i=2; i<plen; i++){
        if (a[i] != b[i]) return false; 
    }
    return true; 
}

vector<int> rmq(int begin, int end){
    int k= log2(end - begin +1);
    return lcmFactor(table[begin][k], table[end - (1 << k) + 1][k]); 
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("A100570.inp", "r"))
    {
        freopen("A100570.inp", "r", stdin);
        freopen("A100570.out", "w", stdout);
    }
    int m, x;
    cin >> n >> m;
    const int hold = (int)1e9 + 7;
    vector<int> a(n);
    vector<vector<int>> ans(n+1); 
    prime(prm); 
    table.assign(n, vector<vector<int>>(log2(n) +1, vector<int>(plen, 0))); 
    for (int i=0; i<n; i++){
        cin >> a[i]; 
        table[i][0]= factor(a[i]); 
    }
    for (int j=1; (1 << j) <= n; j++){
        int lim= n + 1 - (1 << j); 
        for (int i=0; i < lim; i++){
            table[i][j]= lcmFactor(table[i][j-1], table[i + (1 << (j-1))][j-1]); 
        }
    }
    for (int x= 1; x < n+1; x++){
        ans[x]= rmq(0, x-1); 
    }
    
    for (int i=0; i< n; i++){
        int j = i;
        while (j < n)
        {
            vector<int> d = rmq(i,j);
            int t = j;
            for (int k = log2(n - j + 1); k >= 0; k--)
            {
                vector<int> temp= rmq(j,t + (1 << k) -1); 
                if (t < n && checkFactor(d, temp))
                {
                    t = t + (1 << k) - 1; 
                }
            }
            for (int k = j; k < t + 1; k++)
            {
                ans[k - i + 1] = minFactor(ans[k - i + 1], d);
            }
            j = t++;
        }

    }
    return 0;
}