#include <bits/stdc++.h>
using namespace std;

void findmax(int a, int i, stack<pair<int, int>> &s, vector<int> &curMax){
    while(!s.empty() && s.top().first < a){
        s.pop(); 
    }
    if (s.empty()) {
        s.push({a, i});
        return; 
    }
    if (s.top().first > a){
        curMax[i]= s.top().second; 
        s.push({a,i}); 
        return; 
    }

}

int main(){
    if(fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int n; 
    cin >> n; 
    vector<int> nums(n);
    vector<int> rMax(n, -1), lMax(n, -1); 
    stack<pair<int, int>> stackRight, stackLeft; 
    for (int i=0; i<n; i++){
        cin >> nums[i]; 
    }
    for (int i=0; i<n; i++){
        lMax[i]= i; 
        findmax(nums[i], i, stackLeft, lMax); 
    }
    for (int i=n-1; i>=0; i--){
        rMax[i]= i; 
        findmax(nums[i], i, stackRight, rMax); 
    }
    int ans= 0; 
    for (int i=0; i<n-1; i++){
        int next= nums[i] ^ nums[i+1]; 
        // cout << "left: " << lMax[i] << " right: "<< rMax[i]<<"\n"; 
        ans= max({ans, next, nums[i]^nums[rMax[i]], nums[i]^nums[lMax[i]],nums[rMax[i]] ^nums[lMax[i]] }); 
    }
    cout << ans; 
    return 0; 
}