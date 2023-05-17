#include <bits/stdc++.h>
using namespace std;

const int base = 31;
const int MOD = (int)1e9 + 69;
const long long MODSQ = 1ll * MOD * MOD;
vector<long long> Pow;
vector<long long> T, S;
map<long long, int> hashT;
string s, t;

long long hashh(int i, int j, vector<long long> &X)
{
    if (i == 0)
        return X[j];
    return (X[j] - X[i - 1] * Pow[j - i + 1] % MOD + MODSQ) % MOD;
}

pair<char, char> comp(int n)
{
    const int lenP= 'Z' -'A' +1; 
    vector<int> position(lenP, 0);
    pair<char, char> ans= {'A', 'A'}; // pair {s[i], t[j]} need to repalce
    int count= 0; 
    for (int i = 0; i < n; i++)
    {
        position[t[i] - 'A']++;
        position[s[i] - 'A']--;
    }
    for (int i = 0; i < lenP; i++)
    {
        if (position[i] == -1)
            {ans.first = (char)(i + 'A');
            count ++; }
        else if (position[i] == 1)
            {ans.second = (char)(i + 'A');
            count++; }
    }
    if (count != 2 && count != 0) return {' ', ' '};
    return ans;
}

int main()
{

    int n;
    cin >> s >> t;
    n = s.length();
    string tt = t + t;
    string ss = s + s;

    T.assign(n * 2, 1);
    S.assign(n * 2, 1);
    T[0] = t[0] - 'A' + 1;
    S[0] = s[0] - 'A' + 1;
    for (int i = 1; i < n * 2; i++)
    {
        T[i] = (T[i - 1] * base + tt[i] - 'A' + 1) % MOD;
        S[i] = (S[i - 1] * base + ss[i] - 'A' + 1) % MOD;
    }
    Pow.assign(n + 1, 1);
    for (int i = 1; i < n+1; i++)
    {
        Pow[i] = Pow[i - 1] * base % MOD;
    }

    for (int i = 0; i < n; i++)
    {
        long long temp = hashh(i, i + n - 1, T);
        if (hashT.count(temp) == 0)
            hashT[temp] = 1;
        else
            hashT[temp]++;
    }

    long long hashX;
    pair<char, char> hold = comp(n);
    int ans = 0;
    if (hold.first == ' ') {
        cout << 0; 
        return 0;
    }

    if (hold.first == hold.second)
    {
        hashX = hashh(0, n - 1, T);
        for (int i = 0; i < n; i++)
        {
            if (hashh(i, i + n - 1, S) == hashX)
                ans++;
        }
        cout << ans * n;
        return 0;
    }
    for (int i = n * 2 - 1; i > n - 1; i--)
    {
        if (ss[i] == hold.first)
        {
            hashX = (hashh(i - n + 1, i, S) - hold.first + hold.second + MODSQ) % MOD;
            if (hashT.count(hashX) != 0)
                ans += hashT[hashX];
        }
    }
    cout << ans;
    return 0;
}