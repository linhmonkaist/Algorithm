#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<double> p(n+1, 0);
    double temp;
    for (int i=1; i<n+1; i++){
        cin >> temp; 
        p[i]= temp; 
    }
    vector<vector<double>> ans(n+1,vector<double>(n+1,0));
    ans[0][0]= 1;
    for (int i=1; i<n+1; i++){
        ans[i][0] = ans[i-1][0]* (1- p[i]);
        for (int j=1; j< i+1; j++){
            ans[i][j]= ans[i-1][j-1]*p[i] + ans[i-1][j]*(1 - p[i]);
        }
    }
    double sumProb=0;
    for (int i= n/2+1; i<n+1; i++ ){
        sumProb = sumProb + ans[n][i];
    }
    cout << setprecision(10) << sumProb;
    return 0; 
}