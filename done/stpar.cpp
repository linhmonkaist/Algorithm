#include <bits/stdc++.h>
using namespace std; 

bool valid(int a, stack<int> &side){
    if (side.empty()) return true; 
    if (side.top() > a) return true; 
    return false; 
}

void stpar(vector<int> &nums, int n){
    stack<int> side; 
    int point= 1; 
    for (int i=0; i<n; i++){
        if (!side.empty() && side.top() == point){
            side.pop();
            point++;
            i--;  
            continue;
        } 
        if (valid(nums[i], side)) {
            side.push(nums[i]); 
            }
        else {
            cout << "no";
            return; 
        }
        if (side.top() == point){
            side.pop();
            point++; 
        } 
    }
    cout << "yes";
    return; 
}

int main(){
    if(fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int n, end, st = 0;  
    while (cin >> n){
        if(st) cout << "\n";
        else st = 1;
        vector<int> nums(n); 
        for (int i=0; i<n; i++){
            cin >> nums[i]; 
        }
        stpar(nums, n); 
        // cout << (8 ^ 7); 
        // cin >> n; 
        // if (n != 0) cout << endl; 
    }
    return 0; 
}