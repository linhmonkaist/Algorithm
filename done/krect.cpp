#include <bits/stdc++.h>
using namespace std;
int m,n,k; 
int const alpha= 26; 
vector<vector<int>> last_x;
vector<int> h, last_y; 
long long ans= 0; 
int count_h(int j, int col){
    int count= 0;
    for (int char_i= 0; char_i< alpha; char_i++){
        if (last_x[col][char_i] >= j){
            count++; 
            last_y[char_i]= col; 
        }
    }
    return count; 
}

int update_uni(int row_j, int next, int unique){
    if (next >= n) return unique; 
    h[next]= count_h(row_j, next);
    for (int i=0; i< alpha; i++){
        if (last_x[next][i] >= row_j){
            h[last_y[i]]--; 
            unique--; 
        }
    }
    return unique + h[next]; 
}

int rect(int cur){
    for (int row_j= 0; row_j<= cur; row_j++){
        int begin= 0, mid= 0, end= 0, unique; 
        h.assign(n, 0);
        last_y.assign(alpha, -1);  
        h[0]= count_h(row_j, 0); 
        unique= h[0];
        while (end < n){
            if (unique == k) {
                ans += mid - begin + 1;
                end++; 
                update_uni(row_j, end, unique); 
                continue;
            }
            if (unique < k){
                
            }
        }
    }
}
int main(){
    cin >> m >> n >> k; 
    last_x.assign(n, vector<int>(alpha, -1)); 
    char temp; 
    for (int i= 0; i< m; i++){
        for (int j= 0; j< n; j++){
            cin >> temp; 
            last_x[j][temp - 'A']= i;
        }
        rect(i); 
    }
}