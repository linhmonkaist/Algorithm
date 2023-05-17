#include <bits/stdc++.h>
using namespace std;

void check(stack<int> &sub, int a, int i, int &length, int &begin){
    if (sub.empty()) {
        sub.push(a);
        begin= i ; 
        return; 
    }
    if (sub.top() < a){
        sub.push(a);
        return; 
    }
    while (sub.top() <= a)
    {
        
    }
    
}

int main(){
    int n, k; 
    cin >> n >> k; 
    int ans; 
    vector<int> nums(n);
    vector<int> right(n, -1); 
    stack<pair<int, int>> sub; 
    for (int i=0; i<n; i++){
        cin >> nums[i];
    }
    for (int i=0; i<n; i++){
        if (sub.empty() || sub.top().first > nums[i]) {
            sub.push({nums[i], i});
            continue;
        }
        while( !sub.empty() && sub.top().first < nums[i]){
            right[sub.top().second] = i; 
            sub.pop(); 
        }
        sub.push({nums[i], i}); 
    }
}