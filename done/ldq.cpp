#include <bits/stdc++.h>
using namespace std;

int n; 
int M, half; 
vector<int> a;
vector<int> firstset, lastset; 

void gen(){
    for (int i=1; i < M+1; i++){
        int gap= 0, lgap= 0; 
        for (int j= 0; j < half; j++){
            if ((i >> j) & 1) gap += a[j], lgap += a[j + half];
            else gap -= a[j], lgap -= a[j + half]; 
        }
        firstset.push_back(gap); 
        if (n%2 == 1){
            lgap -= a.back();
            lastset.push_back(lgap);
            lgap += a.back() * 2;
        }
        lastset.push_back(lgap); 
    }
}

int main(){
    cin >> n; 
    a.assign(n, 0);
    for (int i=0; i<n; i++){
        cin >> a[i]; 
    }
    M= (1 << (n/2)); 
    half= n/2; 
    gen(); 
    sort(firstset.begin(), firstset.end());
    sort(lastset.begin(), lastset.end());
    int min_set= abs(firstset[0]+ lastset.back());  
    int count= 0;
    int temp; 
    for (int i=0; i < firstset.size()/2; i++){
        int x= firstset[i];
        int j = lower_bound(lastset.begin(), lastset.end(), -x) - lastset.begin();
        int k = upper_bound(lastset.begin(), lastset.end(), lastset[j]) - lastset.begin();
        temp = abs(x + lastset[j]);
        if (temp == min_set)
            count += k - j;
        else if (temp < min_set)
            min_set = temp, count = k - j;
        int minus_j = lower_bound(lastset.begin(), lastset.end(), x) - lastset.begin();
        if (lastset[minus_j] != -lastset[j])
        {
            k = upper_bound(lastset.begin(), lastset.end(), lastset[minus_j]) - lastset.begin();
            temp = abs(x - lastset[minus_j]);
            if (temp == min_set)
                count += k - minus_j;
            else if (temp < min_set)
                min_set = temp, count = k - minus_j;
        }
    }
    cout << min_set << ' '<< count; 
    return 0;
} 