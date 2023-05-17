#include <bits/stdc++.h>
using namespace std; 

const int numDigits= 10; 

void jnext(int n){
    vector<int> digits(n);
    for (int i=0; i<n; i++){
        cin >> digits[i];
    }
    int i= n-1;
    while (i > 0){
        if (digits[i] > digits[i-1]) {
            break; 
        }
        i--; 
    }
    if (i==0){
        cout << -1; 
        return; 
    }
    int hold= digits[i-1]; 
    // cout << "i: "<< i << "\n"; 
    vector<int> count(numDigits, 0); 
    for (int j= n-1; j > i-1; j--){
        count[digits[j]]++; 
    }
    for (int j=hold +1; j<numDigits; j++){
        if (count[j] > 0){
            digits[i-1]= j; 
            count[j] --; 
            count[hold]++; 
            break; 
        }
    }

    for (int k=0; k<i; k++){
        cout<< digits[k];
    }
    for (int k=0; k< numDigits; k++){
        cout << string(count[k], k);
    }
    return; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T, n; 
    cin >> T; 
    for (int i=0; i<T; i++){
        cin >> n; 
        jnext(n); 
        cout << "\n";
    }
    return 0; 
}