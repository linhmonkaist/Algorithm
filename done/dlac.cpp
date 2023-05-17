#include <bits/stdc++.h>
using namespace std;

int find(int u, int v, vector<int> &h, vector<vector<int>> &p)
{
    if (h[u] < h[v])
        swap(u, v);
    for (int j = log2(h[u]); j >= 0; j--)
    {
        if (h[u] - (1 << j) >= h[v])
        {
            u = p[u][j];
        }
    }
    if (u == v)
    {
        return u;
    }

    for (int j = log2(h[u]); j >= 0; j--)
    {
        if (p[u][j] != p[v][j])
        {
            u = p[u][j];
            v = p[v][j];
        }
    }
    return p[u][0];
}

void lca(int n)
{
    int v, u;
    vector<vector<int>> p;
    vector<int> h;
    vector<int> a[n + 1];

    h.assign(n + 1, 0);
    p.assign(n + 1, vector<int>(log2(n + 1) + 1, -1));
    for (int i = 1; i < n; i++)
    {
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    function<void(int, int)> dfs = [&](int t, int par)
    {
        p[t][0] = par;
        h[t] = h[par] + 1;
        for (int j = 1; (1 << j) < n; j++)
        {
            p[t][j] = p[p[t][j - 1]][j - 1];
        }
        for (int &child : a[t])
        {
            if(child == par) continue;
            dfs(child, t);
        }
        return;
    };
    h[1] = -1;
    dfs(1, 1);

    int m;
    cin >> m;
    int root;
    root = 1;
    string s;
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        if (s == "?")
        {
            cin >> u >> v;
            int uv = find(u, v, h, p);
            int ur = find(u, root, h, p);
            int vr = find(v, root, h, p);
            // cout << uv << " "<< ur << " "<< vr << "\n";
            if (ur == vr)
            {
                cout << uv << "\n";
                continue;
            }
            if (ur == root || vr == root)
            {
                cout << root << "\n";
                continue;
            }
            if (h[ur] > h[vr])
            {
                cout << ur << "\n";
                continue;
            }
            cout << vr << "\n";
        }
        else
        {
            cin >> root;
        }
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("input.txt", "r"))
    {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int n;
    while (cin >> n)
    {
        if(n == 0) return 0;
        lca(n);
    }
}