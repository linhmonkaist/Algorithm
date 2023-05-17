 #include <bits/stdc++.h>
using namespace std;

int main(){
    int m[]= {20,2,0,0,3,0,4,5,0,7,0,0,3,4};
    vector<int> v(m, m + 14);
    int begin= 0, t=0, cur=0, n=14, k=7;
    int sum= 0, count= 0; 
    while(cur < n && sum < k){
        sum += v[cur];
        cur++;
    } 
    cur--; 
    while (cur < n){
        if(sum == k) {
            count += t - begin +1; 
            cur++;
            if (cur < n) sum += v[cur];
            continue;
        }
        if(sum > k){
            begin= t; 
            while (begin < cur && sum > k){
                sum -= v[begin];
                begin++; 
            }
            t= begin; 
            int temp= sum; 
            while (temp == sum && t < cur){
                t++; 
                temp -= v[t];
            }
            continue;
        }
        cur++; 
        sum += v[cur]; 
    }
    cout << count; 
}