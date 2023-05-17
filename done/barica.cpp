#include <bits/stdc++.h>
using namespace std;

int n, k; 
struct point{
    int index, x, y, f;
};

int main(){
    if (fopen("test.inp", "r")){
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout); 
    }
    cin >> n >> k; 
    vector<point> p(n);
    for (int i=0; i<n; i++){
        cin >> p[i].x >> p[i].y >> p[i].f;
        p[i].index= i;
    }
    sort(p.begin(), p.end(), [](point &u, point &v){
        if (u.x != v.x) return u.x < v.x; 
        return u.y < v.y; 
    });
    // for (int i=0; i<n; i++){
    //     cout << p[i].index <<' ' << p[i].x << ' ' << p[i].y << ' '<< '\n';
    // }
    map<int, int> lastX, lastY; 
    int begin= 0; 
    for (int i=0; i<n; i++) if(p[i].index== 0) begin= i; 
    lastX[p[begin].x]= p[begin].f;
    lastY[p[begin].y]= p[begin].f; 
    for (int i=begin + 1; i<n; i++){
        long long power, pointX= INT_MIN + k, pointY= INT_MIN + k; 
        if (lastX.count(p[i].x) == 0 && lastY.count(p[i].y) == 0) continue;
        if (lastX.count(p[i].x) != 0) pointX= lastX[p[i].x]; 
        if (lastY.count(p[i].y) != 0) pointY= lastY[p[i].y];
        power= max(pointX + p[i].f - k, pointY + p[i].f - k);
        if(p[i].index == n-1) {
            cout << power;
            return 0; 
        }
        if (power >= k){
            lastX[p[i].x]= max(pointX, power);
            lastY[p[i].y]= max(pointY, power);
        }
        // cout << i <<' ' << pointX << ' ' << pointY << ' '<< power << ' '<< lastX.size()<< ' ' << lastY.size()<< '\n';
    }
    return 0; 
}
