#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string s,t;
    cin >> s >> t;
    int lenS= s.length();
    int lenT= t.length();
    vector<vector<int>> ans(lenS+1, vector<int>(lenT+1,0));
    for (int i=1; i< lenS+1; i++){
        for (int j=1; j< lenT+1; j++){
            if (s[i-1] == t[j-1]) ans[i][j] = ans[i-1][j-1] + 1;
            else ans[i][j]= ans[i-1][j] > ans[i][j-1]? ans[i-1][j]:ans[i][j-1];
        }
    }
    int i=lenS, j= lenT;
    string hold= "";
    while (i>0 && j>0){
        if (s[i-1]== t[j-1]){
            hold += s[i-1];
            i--;
            j--;
        } else{
            if (ans[i-1][j]> ans[i][j-1]) i--;
            else j--;
        }
    }
    reverse(hold.begin(), hold.end());
    cout << hold;
    return 0;
}