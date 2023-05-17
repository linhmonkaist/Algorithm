#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<int> minH[2];

void check(int j, int cur, vector<int> &h, stack<pair<int, int>> &hold)
{
    pair<int, int> temp;
    while (!hold.empty())
    {
        temp = hold.top();
        if (temp.first >= h[j])
            hold.pop();
        else
            break;
    }
    if (hold.empty())
    {
        minH[cur][j] = cur == 0 ? -1 : n;
    }
    else
    {
        minH[cur][j] = hold.top().second;
    }
    hold.push({h[j], j});
    return;
}

void kagain(int n)
{
    vector<int> numA(n, 0);
    int begin, end;
    minH[0].clear();
    minH[1].clear(); 
    minH[0].assign(n, -1);
    minH[1].assign(n, -1);
    for (int i = 0; i < n; i++)
    {
        cin >> numA[i];
    }

    stack<pair<int, int>> hold;
    for (int i = 0; i < n; i++)
    {
        check(i, 0, numA, hold);
    }
    stack<pair<int, int>> bhold;
    for (int i = n - 1; i >= 0; i--)
    {
        check(i, 1, numA, bhold);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int temp = numA[i] * (minH[1][i] - minH[0][i] - 1);
        if (temp > ans)
        {
            ans = temp;
            begin = minH[0][i] + 1 + 1;
            end = minH[1][i];
        }
    }
    cout << ans << " " << begin << " " << end;
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> n;
        kagain(n);
        cout << endl;
    }
    return 0;
}