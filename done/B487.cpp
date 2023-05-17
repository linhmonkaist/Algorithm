#include <bits/stdc++.h>
using namespace std;

pair<int, int> findMin(vector<int> &a, int n, vector<int> &lMin, int l, vector<int> &lMax){
    vector<vector<int>> table(n, vector<int>(n));
    vector<vector<int>> tableMax(n, vector<int>(n));
    for (int i=0; i<n; i++){
        table[i][0]= a[i];
        tableMax[i][0]= a[i]; 
    }
    int colSize= log2(n) +1; 
    for (int j=1; j< colSize; j++){
        for (int i=0; i< n - (1 << j) + 1; i++){
            int gap= 1 << (j-1); 
            if( table[i+ gap][j-1] <= table[i][j-1]) table[i][j]= table[i + gap][j-1];
            else table[i][j]= table[i][j-1];

            if( tableMax[i+ gap][j-1] >= tableMax[i][j-1]) tableMax[i][j]= tableMax[i + gap][j-1];
            else tableMax[i][j]= tableMax[i][j-1];
        }
    }
    int k= log2(l); 
    for (int i=0; i<n-l+1; i++){
        if (table[i][k] <= table[i + l - (1 << k)][k]) lMin[i]= table[i][k];
        else lMin[i]= table[i + l - (1 << k)][k]; 

        if (tableMax[i][k] >= tableMax[i + l - (1 << k)][k]) lMax[i]= tableMax[i][k];
        else lMax[i]= tableMax[i + l - (1 << k)][k]; 
        cout << "max: " << lMax[i] << " min: " << lMin[i] << "\n"; 
    }
}

// void greedy(){
//         vector<int> valid(n-l+1);
//     for (int i=0; i< n-l+1; i++){
//         valid[i]= lMax[i] - lMin[i]; 
//     }
    
//     if (valid[0] > s || valid[n-l] > s) {
//         cout << -1; 
//         return 0; 
//     }
//     int count= 0; 
//     for (int i=0; i< n-l+1; i++){
//         int temp= valid[i]; 
//         int cur= i+l; 
//         int k= l; 
//         while (temp <= s && cur < n-l){
//             if ( max(lMax[i] - a[cur], a[cur] - lMin[i]) <= s && valid[cur+1] <= s){
//                 if (a[cur] > lMax[i]) lMax[i]= a[cur]; 
//                 else if (a[cur] < lMin[i]) lMin[i]= a[cur]; 
//                 cur++;
//                 temp= lMax[i]- lMin[i];
//             } else {
//                 count ++; 
//                 i= cur-1; 
//                 cout << " cur: "<<cur << "\n";
//                 break; 
//             }
//         }
//     }
//     cout << count; 
// }

int main(){
    int n, l,s; 
    cin >> n >> l >> s; 
    vector<int> a(n);
    vector<int> lMin(n-l+1, 0), lMax(n-l+1, 0); 
    for (int i=0; i<n; i++){
        cin >> a[i]; 
    }
    findMin(a, n, lMin, l, lMax);

    const int inf= (int) 1e5 +10; 
    vector<int> ans(n, inf);
    if (lMax[0] - lMin[0] <= s) {
        ans[l-1]= 1; 
    } else {
        cout << -1; 
        return 0; 
    }
    
    // int pos= 0;
    // for (int i=l; i<n; i++){
    //     while ()
    // }
    return 0; 
}