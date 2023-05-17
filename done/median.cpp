#include <bits/stdc++.h>
using namespace std;
int n, k;
const int divisor= 65536; 
typedef pair<int, int> ele; 
vector<ele> a; 
vector<int> checkSet; 

struct Less
{
    bool operator()(const ele& x, const ele& y) {
        if(x.first != y.first) return x.first > y.first;
        return x.second > y.second;
    }
};

bool compare(const ele& x, const ele& y) {
    if(x.first != y.first) return x.first > y.first;
    return x.second > y.second;
}

void check(priority_queue<ele> &x, priority_queue<ele, vector<ele>, greater<ele>> &y, int begin){
    while (!x.empty() && x.top().second < begin -1){
        x.pop(); 
    }
    while (!y.empty() && y.top().second < begin -1){
        y.pop(); 
    }
}

void median(){
    long long ans= 0; 
    checkSet.clear(); 
    checkSet.assign(n, -1);
    vector<ele> temp(a.begin(), a.begin() + k); 
    sort(temp.begin(), temp.end(), compare);
    for (ele &x: temp) cout << x.first << ' '<< x.second << '\n';  
    priority_queue<ele, vector<ele>, greater<ele>> hi; 
    for (int i= k/2; i<k; i++) {hi.push(temp[i]); checkSet[temp[i].second]= 1;}
    priority_queue<ele> lo;
    for (int i=0; i< (k+1)/2; i++) {lo.push(temp[i]); checkSet[temp[i].second]= 0;}
    int begin= 1, end= k; 
    bool odd= k % 2;
    if (odd && k > 1) hi.pop(); 
    while (end < n){
        check(lo, hi, begin); 
        ele left_me= lo.top();
        ele right_me= hi.top(); 
        // cout << left_me.first << ' '<< right_me.first << '\n'; 
        ans+= left_me.first; 
        if (checkSet[begin-1] == 0 && a[end].first >= right_me.first){
            lo.push(right_me); 
            checkSet[right_me.second]= 0; 
            hi.pop();
            hi.push(a[end]); 
            checkSet[end]= 1;
            begin ++, end ++;
            continue;
        }
        if (checkSet[begin -1] == 0 && a[end].first < right_me.first){
            lo.push(a[end]);  
            checkSet[end] = 0; 
            begin ++, end ++; 
            continue;
        }
        if (checkSet[begin -1] == 1 && a[end].first < left_me.first){
            hi.push(left_me); 
            checkSet[left_me.second]= 1; 
            lo.pop();
            lo.push(a[end]); 
            checkSet[end]= 0;  
            begin ++, end ++;
            continue;
        }
        hi.push(a[end]);
        checkSet[end] = 1;
        begin++, end++;
    }
    check(lo, hi, begin);
    // cout << lo.top().first << ' '<< hi.top().first << '\n'; 
    ans += lo.top().first;
    cout << ans << '\n'; 
}

int main(){
    int mul, add, seed, t; 
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> t; 
    for (int j=0; j<t; j++){
        cin >> seed >> mul >> add >> n >> k; 
        a.assign(n, {seed, 0});
        long long ans1 = seed;
        for (int i=1; i<n; i++){
            a[i].first= (1ll * a[i-1].first * mul % divisor + add) % divisor; 
            a[i].second= i; 
            ans1 += a[i].first;
            // cout << a[i].first << ' ';
        }
        // cout << '\n';
        cout << "Case #" << j+1 << ": "; 
        if(k == 1) cout << ans1 << '\n';
        else median(); 
    }

    return 0; 
}