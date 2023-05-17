#include <bits/stdc++.h>
using namespace std;

vector<vector<unsigned long long>> table;

unsigned long long lcm(unsigned long long a, unsigned long long b){
    return 1ll * a * b / __gcd(a, b);
}

unsigned long long rmq(int begin, int end, vector<vector<unsigned long long>> &table){
    int k= log2(end - begin +1);
    return lcm(table[begin][k], table[end - (1 << k) + 1][k]); 
}

int main()
{
    
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    if (fopen("A100570.inp", "r"))
    {
        freopen("A100570.inp", "r", stdin);
        freopen("A100570.ans", "w", stdout);
    }
    int n, m;
    cin >> n >> m;
    const long long hold = (int)1e9 + 7;
    vector<unsigned long long> a(n);
    vector<unsigned long long> ans(n+1, LLONG_MAX);
    table.assign(n, vector<unsigned long long> (log2(n) +1, 1)); 

    for (int i=0; i < n; i++){
        cin >> a[i]; 
        table[i][0]= a[i];
    }
    for (int j = 1; (1 << j) <= n; j++)
    {
        int lim = n + 1 - (1 << j);
        for (int i = 0; i < lim; i++)
        {
            table[i][j] = lcm(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }

    for (int x = 1; x < n + 1; x++)
    {
        for (int i = 0; i + x -1 < n; i++)
        {
            unsigned long long d = rmq(i, i + x - 1, table);
            ans[x]= min(ans[x], d);
        }
    }
    int x; 
    for (int i=0; i<m; i++){
        cin >> x;
        cout << ans[x] % hold <<"\n"; 
    }
    return 0;
}