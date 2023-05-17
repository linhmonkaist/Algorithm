#include <bits/stdc++.h>
using namespace std;
int n, s, l;

void qadd(deque<int> &qMin, deque<int> &qMax, int i, vector<int> &a)
{
    while (!qMin.empty() && a[qMin.back()] >= a[i])
    {
        qMin.pop_back();
    }
    while (!qMax.empty() && a[qMax.back()] <= a[i])
    {
        qMax.pop_back();
    }
    qMin.push_back(i);
    qMax.push_back(i);
}

int check(deque<int> &smin, deque<int> &smax, int i, vector<int> &a, int pos)
{
    if (smin.front() < pos)
        smin.pop_front();
    if (smax.front() < pos)
        smax.pop_front();
    while (!smin.empty() && a[smin.back()] >= a[i])
    {
        smin.pop_back();
    }
    while (!smax.empty() && a[smax.back()] <= a[i])
    {
        smax.pop_back();
    }
    smax.push_back(i);
    smin.push_back(i);
    return a[smax.front()] - a[smin.front()];
}

int main()
{
    cin >> n >> s >> l;
    vector<int> a(n);
    int lmin, lmax;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    deque<int> smin, smax;

    for (int i = 0; i < l; i++)
    {
        qadd(smin, smax, i, a);
    }

    const int inf = (int)1e5 + 10;
    vector<int> ans(n + 1, inf);
    ans[0] = 0;
    if (a[smax.front()] - a[smin.front()] <= s)
    {
        ans[l] = 1;
    }
    else
    {
        cout << -1;
        return 0;
    }

    int pos = 1;
    deque<int> hold;
    hold.push_back(1);
    for (int i = l + 1; i < n + 1; i++)
    {
        while (!hold.empty() && ans[hold.back() - 1] > ans[i - l])
        {
            hold.pop_back();
        }
        hold.push_back(i - l + 1);
        while (check(smin, smax, i - 1, a, pos - 1) > s && i - pos + 1 >= l)
        {
            pos++;
            if (!hold.empty() && hold.front() < pos)
                hold.pop_front();
        }

        if (check(smin, smax, i - 1, a, pos - 1) <= s && i - pos + 1 >= l && !hold.empty())
        {
            ans[i] = min(ans[hold.front() - 1] + 1, inf);
            // cout << i << " ans[i]: " << ans[i] << " pos: " << pos << "\n";
        }
    }
    if (ans[n] == inf)
        cout << "-1";
    else
        cout << ans[n];
    // for (int i=0; i<n+1; i++){
    //     cout << ans[i] << " ";
    // }
    // l= 1;
    // int k= log2(l);
    // for (int i=0; i<n-l+1; i++){
    // findMin(4,5, lmax, lmin);
    // cout << "max: " << lmax << " min: " << lmin << "\n";
    // }
    return 0;
}