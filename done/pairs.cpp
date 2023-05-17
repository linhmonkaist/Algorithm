#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    long long ans = 0;
    int temp;
    stack<pair<int, int>> hold;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        if (hold.empty())
        {
            hold.push({temp, 1});
            continue;
        }
        while (!hold.empty() && hold.top().first < temp)
        {
            ans += hold.top().second;
            hold.pop();
        }
        if (!hold.empty() && hold.top().first > temp)
        {
            ans += 1;
            hold.push({temp, 1});
            continue;
        }
        if (!hold.empty() && hold.top().first == temp)
        {
            pair<int, int> in = hold.top();
            ans += in.second; 
            in.second++;
            hold.pop();
            hold.push(in);
            if (hold.size() > 1) ans += 1; 
            continue;
        }
        hold.push({temp, 1});
        // cout << ans << " ";
    }
    cout << ans;
    return 0;
}