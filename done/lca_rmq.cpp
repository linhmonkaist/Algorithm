#include <bits/stdc++.h>
using namespace std;

vector<int> t,h; 
int n;
vector<vector<int>> a; 
vector<vector<int>> table; 

void dfs(vector<int> &e, vector<int> &l, int &j, int vertex){
    e[j]= vertex; 
    l[j]= h[vertex];
    j++; 
    if (a[vertex].size() == 0){
        return; 
    } 
    for (int &child: a[vertex]){
        dfs(e,l, j, child); 
        e[j]= vertex; 
        l[j]= h[vertex];
        j++; 
    }
    return; 
}

int rmq(int i , int j, vector<int> &l){
    int gap= log2(j-i+1); 

    return min(table[i][gap], table[j - (1 << gap) +1][j]); 
}

void lca(){
    int temp, child; 
    cin >> n; 
    vector<int> e(2*n), l(2*n), h(n+1, 0); 
    t.assign(n+1, 0), h.assign(n+1, -1); 
    vector<int> row; 
    a.push_back(row); 
    for (int i=1; i<n+1; i++){
        cin >> temp; 
        row.assign(temp, 0); 
        for (int j= 0; j<temp; j++){
            cin >> child; 
            h[child]= h[i] +1;
            t[child]= i;
            row[j]= child; 
        }
        a.push_back(row); 
    }
    int j= 1;
    dfs(e, l, j, 1); 
    for (int i= 1; i < 2*n; i++){
        if (h[e[i]] == 0){
            h[e[i]]= i; 
        }
    }
    int sz= l.size(); 
    const int colSize= log2(sz) +1; 
    table.assign(sz, vector<int>(colSize)); 
    for (int i=1; i<sz; i++){
        table[i][0]= i; 
    }
    for (int j=1; (1<<j) <= sz; j++){
        for (int i=1; i< sz + 1 - (1<<j); i++){
            table[i][j]= min(table[i][j-1], table[i + (1 << (j-1))][j-1]); 
        }
    }

    int q, u,v; 
    cin >> q; 
    for (int i=0; i<q; i++){
        cin >> u >> v; 
        cout << e[rmq(h[u],h[v], l)]; 
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int test; 
    cin >> test;
    for(int i=0; i<test; i++){
        lca(); 
    }
    return 0; 
}