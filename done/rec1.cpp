#include <bits/stdc++.h>
using namespace std;

int m, n;

int minJ(vector<int> &h, vector<int>& minH)
{
    int area = 0;
    stack<pair<int, int>> hold;
    pair<int, int> temp;

    auto forH(int j, int cur){
        if (h[j] == 0){
            while(!hold.empty()) hold.pop(); 
            return; 
        }
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
            hold.push({h[j], j});
            minH[cur][j] = -1;
        } else{
            minH[cur][j]= hold.top().second;
        }
        return;
    }
        for (int i = 0; i < n; i++)
        {
            forH(i,0); 
        }
        for (int i=n-1; i>= 0; i--){
            forH(i,1); 
        }
    for (int i=0; i<n; i++){
        if (minH[0][i] == -1 && minH[1][i] == -1) 
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n;
    vector<int> h(n, 0);
    vector<int> minH[2]; 
    minH[0].assign(n,-1); 
    minH[1].assign(n, -1); 
    int temp;
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> temp;
            if (temp == 1)
                h[j] += 1;
            else
                h[j] = 0;
        }

        ans = max(ans, recJ(h));
    }
    cout << ans;
    return 0;
}