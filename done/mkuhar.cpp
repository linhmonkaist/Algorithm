#include <bits/stdc++.h>
using namespace std;
int n, c; 
int const max_weight= (int)1e6+107;  
struct ingre{
    int x, y, sizeM, pM, sizeL, pL; 
}; 
vector<vector<int>> p; 
vector<ingre> rcp;

long long price(int weight, int i){
    if (weight >= max_weight) return c + 1;
    if (weight <= 0) return 0; 
    long long ans = c + 1;
    long long cur = 0;
    while(weight >= 0 && cur <= c) {
        ans = min(ans, cur + (weight + rcp[i].sizeM - 1) / rcp[i].sizeM * rcp[i].pM);
        cur += rcp[i].pL;
        weight -= rcp[i].sizeL;
    }
    if(weight <= 0) ans = min(ans, cur);
    return ans;
}
int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> c;  
    rcp.resize(n); 
    for (int i=0; i<n; i++){
        cin >> rcp[i].x >> rcp[i].y >> rcp[i].sizeM >> rcp[i].pM >> rcp[i].sizeL >> rcp[i].pL;
    }
    int begin= 0, end= c+100, mid;
    while (begin <= end){
        mid= (begin + end)/2; 
        long long money=0; 
        for (int i=0; i<n; i++){
            int need= mid * rcp[i].x - rcp[i].y; 
            money += price(need, i); 
        }
        if (money <= c) begin= mid +1;
        else end= mid - 1; 
    } 
    cout << begin -1; 
    return 0; 
}
