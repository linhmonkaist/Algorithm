#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<vector<int>> p, ans;
vector<int> h;

int lca(int u, int v)
{
    if (h[u] < h[v])
        swap(u, v);
    for (int i = log2(h[u]); i >= 0; i--)
    {
        if (h[u] - (1 << i) >= h[v])
        {
            u = p[u][i];
        }
    }
    if (u == v)
        return u;
    for (int i = log2(h[u]); i >= 0; i--)
    {
        if (p[u][i] != p[v][i])
        {
            u = p[u][i];
            v = p[v][i];
        }
    }
    return p[u][0];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("test.inp", "r"))
    {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
    cin >> n >> q;
    int u, v;
    h.assign(n + 1, -1);
    vector<int> a[n + 1];
    p.assign(n + 1, vector<int>(log2(n) + 1));
    ans.assign(n + 1, vector<int>(log2(n) + 1));
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        a[v].push_back(u);
        a[u].push_back(v);
    }

    function<void(int, int)> dfs = [&](int t, int par)
    {
        h[t] = h[par] + 1;
        p[t][0] = par;
        ans[t][0] = t;
        for (int j = 1; (1 << j) <= n; j++){
            p[t][j] = p[p[t][j - 1]][j - 1];
        }
        for (int &child : a[t])
        {
            if (child != par)
                dfs(child, t);
        }
        return;
    };
    dfs(1, 1);

    for (int j = 1; (1 << j) <= n; j++)
    {
        int lim = n + 2 - (1 << j);
        for (int i = 1; i < lim; i++)
        {
            ans[i][j] = lca(ans[i][j - 1], ans[i + (1 << (j - 1))][j - 1]);
            // cout << i << " "<< j << " "<< ans[i][j] << "\n";
        }
    }

    for (int i = 0; i < q; i++)
    {
        cin >> u >> v;
        int k = log2(v - u + 1);
        cout << lca(ans[u][k], ans[v - (1 << k) + 1][k]) << '\n';
    }
    return 0;
}