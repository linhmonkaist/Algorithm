#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

int n;

void binary(string& s, vector<string>& ans) {
    if(s.size() == n) {
        ans.push_back(s);
        return;
    }
    s += "0";
    binary(s, ans);
    s.pop_back();
    s += "1";
    binary(s, ans);
    s.pop_back();
}

int main()
{
    cin >> n;
    string s = "";
    vector<string> ans;
    ans.clear();
    binary(s, ans);
    for(string s: ans) {
        cout << s << '\n';
    }
}