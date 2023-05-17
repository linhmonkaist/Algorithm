#include <bits/stdc++.h>
using namespace std;

int n, half, quarter, m; 
vector<int> hi, lo; 

void gen(){
    int max_num= round(pow(10, quarter)); 
    for (int i= round(pow(10, quarter - 1)); i< max_num; i++){
        hi.push_back(i);
        lo.push_back(i); 
    }
    // vector<int> vec(100);
    // iota(vec.begin(), vec.end(), begin);
    max_num= round(pow(10, quarter - 1)); 
    for (int i= 0; i< max_num; i++){
        lo.push_back(i); 
    }
}

int palin(int x){
    int addi= 0; 
    int y= x;
    if (half % 2 == 1) y= x / 10; 
    for (int i=0; i<half - quarter; i++){
        addi = addi * 10 + y % 10; 
        y = y/10; 
    }
    return addi % m; 
}

void remain(){
    int hold= round(pow(10, half- quarter)); 
    hold= hold % m; 
    for (int i= 0; i< hi.size(); i++){
        hi[i]= (palin(hi[i]) + 1ll * hold * (hi[i] % m)) %m; 
    }
    for (int i= 0; i<lo.size(); i++){
        lo[i]= (palin(lo[i]) + 1ll * hold*(lo[i] % m)) %m; 
    }
}

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> m; 
    half= n/2; 
    quarter= (half + 1)/2; 
    long long count= 0; 
    long long hold= round(pow(10, half));
    hold= hold % m;  
    gen();
    remain(); 
    sort(hi.begin(), hi.end());
    sort(lo.begin(), lo.end()); 
    for (int &x: hi){
        int r= (m - ((1ll* x * hold) % m)) % m; 
        int j= lower_bound(lo.begin(), lo.end(), r) - lo.begin();
        int k= upper_bound(lo.begin(), lo.end(), lo[j]) - lo.begin(); 
        if (lo[j] == r) count += k - j; 
    }
    cout << count << '\n'; 
    return 0; 
}