#include <bits/stdc++.h>
using namespace std; 

int main(){
    string s; 
    cin >> s; 
    stack<int> hold; 
    for (char& i: s){
        if (i == '(') {
            hold.push(-1);
            continue;
        }
        if (i == 'C'){
            hold.push(12); 
            continue;
        } 
        if (i == 'H'){
            hold.push(1); 
            continue;
        }
        if (i == 'O'){
            hold.push(16);
            continue;
        } 
        if (i == ')'){
            int add= 0; 
            while (hold.top() != -1){
                add += hold.top(); 
                hold.pop(); 
            }
            hold.pop();
            hold.push(add);
            continue;
        }
        if (i - '0' >= 2 && i - '0' <= 9){
            int temp= hold.top() * (i - '0'); 
            hold.pop();
            hold.push(temp);
        }
    }
    int ans= 0;
    while (!hold.empty()){
        ans += hold.top();
        hold.pop();
    }
    cout << ans; 
    return 0; 
}