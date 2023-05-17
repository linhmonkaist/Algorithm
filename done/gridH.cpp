#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int h,w;
    cin >> h >> w;
    vector<vector<int>> ans(h, vector<int>(w, 1));
    char temp;
    for (int i=0; i<h; i++){
        for (int j=0; j<w; j++){
            cin >> temp; 
            if (temp == '#') {
                ans[i][j]= 0; 
            } 
        }
    }
    for (int j=1; j<w; j++){
        ans[0][j]= ans[0][j] != 0? ans[0][j-1]:0;
    }
    for (int i=1; i<h; i++){
        ans[i][0]= ans[i][0] != 0? ans[i-1][0]:0;
    }
    for (int i=1; i<h; i++){
        for (int j=1; j<w; j++){
            if (ans[i][j] != 0){
                ans[i][j]= (ans[i-1][j] + ans[i][j-1]) % ((int) 1e9+7);
            }
        }
    } 
    cout << ans[h-1][w-1];
    return 0;
}