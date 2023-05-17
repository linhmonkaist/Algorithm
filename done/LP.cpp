#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define maxN 1e5+2
vector<int> adj[(int) maxN];
vector<int> path; 
vector<bool> visit;
//visit and compute max path
int maxPath(int vertex){
    if (visit[vertex]) return path[vertex];
    if (adj[vertex].size()==0) {
        visit[vertex]= true; 
        path[vertex]= 0;
        return 0;
    }
    int tempMax= 0;
    for (int i:adj[vertex]){
        tempMax= max(tempMax, maxPath(i));
        visit[i]= true; 
    }
    path[vertex]= tempMax+1;
    visit[vertex]= true; 
    return tempMax +1; 
}

int main()
{
    int n,m;
    cin >> n >> m;
    
    int pre, post;
    for (int i=0; i<m; i++){
        cin >> pre >> post;
        adj[pre].push_back(post);
    }
    visit.assign(n+1, false); 
    path.assign(n+1, 0); 

    for (int i=1; i< n+1; i++){
        if (!visit[i]) {
            maxPath(i);
        }
    }
    int ans= *max_element(path.begin(), path.end());
    cout << ans;
    return 0;
}