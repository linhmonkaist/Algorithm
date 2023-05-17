#include <bits/stdc++.h>
using namespace std;

void check(int apm, int index, deque<pair<int, int>> &hold)
{

        while (!hold.empty())
        {
            if (apm <= hold.back().first)
            {
                hold.pop_back();
            }
            else
                break;
        }
        hold.push_back({apm, index});

}

void mink(int n, int k){
    vector<int> apm(n, 1); 
    deque<pair<int, int>> hold; 
    for (int i=0; i<n; i++){
        cin >> apm[i]; 
    }
    for (int i=0; i<k; i++){
        check(apm[i],i, hold);
    } 
    cout << hold.front().first << " "; 
    int i= k;
    while (i<n){
        check(apm[i], i, hold); 
        if (hold.front().second < i-k+1) hold.pop_front(); 
            cout << hold.front().first<< " "; 
        i++; 
    }
}

int main(){
    int T, n,k; 
    cin >> T; 
    for (int i=0; i< T; i++){
        cin >> n >> k; 
        mink(n, k);
        cout << endl; 
    }
    return 0;
}