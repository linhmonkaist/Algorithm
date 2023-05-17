#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n,k;
    vector<vector<int>> a;
    cin >> n >> k;
    int temp;
    vector<int> zRow(n+1,0);
    a.push_back(zRow);
    for (int i=0; i<n; i++){
        vector<int> row, ansRow;
        row.push_back(0);

        for (int j=0; j<n; j++){
            cin >> temp;
            row.push_back(temp);

        }
        a.push_back(row);
    }
    
    for (int i=1; i<n+1; i++){
        for (int j=1; j<n+1; j++){
            a[i][j]= a[i-1][j] + a[i][j-1] - a[i-1][j-1] + a[i][j];
        }
    }
    int ansMax=0;
    for (int i=k; i<n+1; i++){
        for (int j=k; j<n+1; j++){
            ansMax= max(a[i][j] -a[i-k][j] - a[i][j-k] + a[i-k][j-k], ansMax);
        }
    }
    cout << ansMax;
    
    return 0;
}
