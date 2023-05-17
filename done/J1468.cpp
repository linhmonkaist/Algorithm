#include <bits/stdc++.h>
using namespace std;

int n, m, k;

struct Edge
{
    int u, v, w;
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w){};
};
vector<Edge> edges;

struct DSU
{
    vector<int> prt;
    DSU(int n)
    {
        prt.assign(n + 3, -1);
    }
    int find_set(int u)
    {
        return prt[u] < 0 ? u : prt[u] = find_set(prt[u]);
    }
    bool join_set(Edge e)
    {
        int u = find_set(e.u);
        int v = find_set(e.v);
        if (u == v) return false;
        if (prt[u] > prt[v]) swap(u, v);
        prt[u] += prt[v];
        prt[v] = u;
        return true;
    }
};

void reform(int n, int m, int k)
{
    long long ans = 0;
    sort(edges.begin(), edges.end(), [](Edge &x, Edge &y)
         { return x.w < y.w; });
    DSU g(n);

    int gap = abs(edges[0].w - k);
    int cur = 0;
    for (int i = 1; i < m; i++)
    {
        if (gap > abs(edges[i].w - k) || (gap == abs(edges[i].w -k) && k > edges[i].w))
        {
            cur = i;
            gap = abs(edges[i].w - k);
        }
    }
    //auto ep = lower_bound(edges.begin(), edges.end(), Edge(0, 0, k), );

    int count= 0;
    int temp= cur;
    bool check;
    while (count < n-1 && cur >= 0){ // lab[find(1)] + n != 0
        check= g.join_set(edges[cur]);
        if (check) count++;
        cur--;
    }
    if (count == n-1){
        cout << abs(k- edges[temp].w) << '\n';
        return;
    }
    if(edges[temp].w > k) ans += edges[temp].w -k;
    while (count < n-1){
        check= g.join_set(edges[temp]);
        if (check) {
            count++;
            ans += edges[temp].w - k;
        }
        temp++;
    }
    long long hold= 0; 
    count = 0; 
    int maxedge= edges[0].w; 
    DSU newG(n); 
    for (Edge &e: edges){
        if (count < n-1 && newG.join_set(e)){
            count++;
            maxedge= e.w; 
            if (maxedge > k) hold += maxedge - k; 
        }
    }
    if (maxedge < k) hold += k- maxedge; 
    cout << min(ans, hold) << '\n';
    return;
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
    int t;
    cin >> t;
    int u, v, s;
    for (int i = 0; i < t; i++)
    {
        cin >> n >> m >> k;
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> s;
            edges.push_back(Edge(u, v, s));
        }
        reform(n, m, k);
        edges.clear();
    }
    return 0;
}