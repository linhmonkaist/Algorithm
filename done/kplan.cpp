#include <bits/stdc++.h>
using namespace std;

int n;
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
    minH[0].assign(n, -1);
    minH[1].assign(n, -1);
    int length= 0; 
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
        
        // int temp = numA[i] * (min(minH[1][i] - minH[0][i] - 1, numA[i]));
        if (numA[i] > length && (minH[1][i] - minH[0][i] - 1) >= numA[i] )
        {
            length= numA[i]; 
        }
    }
    cout << length << "\n"; 
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

        kagain(n);
        cout << endl;

    return 0;
}