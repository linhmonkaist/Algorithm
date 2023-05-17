#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include<math.h>
#include <map>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; 
    cin >> n; 
    string s; 
    map<int, int> countS; 
    int temp= 0;
    for (int i=0; i<n; i++){
        cin >> s; 
        temp= 0;
        for(char& c: s){
            temp= temp ^ (1 << (c - 'a'));
        }
        if (countS.count(temp) == 0) countS[temp]= 1;
        else countS[temp] += 1; 
    }
    long long ans= 0; 
    for (const auto &sPair: countS){
        int hold= sPair.first; 
        ans += 1ll * sPair.second * (sPair.second - 1)/2; 
        for (int i=0; i<26; i++){
            if (((hold >> i) & 1) == 0) {
                temp= hold | (1 << i); 
                if (countS.count(temp) != 0) ans += sPair.second * countS[temp]; 
            }
        }
    }
    cout << ans; 
    return 0; 
}