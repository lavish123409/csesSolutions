#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// void printPQ(auto pq) {
//     cout << "[";
//     while(!pq.empty()) {
//         int d = pq.top().first;
//         int u = pq.top().second;
//         pq.pop();
//         cout << "(" << d << " : " << u << ") , ";
//     }
//     cout << "]\n";
// }

// void markNegativeCycles(bool isInNegativeCycle[], array<int, 3> edges[], int u, int n) {
//     int currentNode = u;
//     do {
//         isInNegativeCycle[u] = 1;
        
//     } while(currentNode != u);
// }

void printArray(array<int,3> e[], int n) {
    int i;
    for(i=0;i<n;i++) {
        cout << e[i][0] << " -> " << e[i][1] << " : " << e[i][2] << "\n";
    }
}

void bellmanFordMaxDistance(array<int,3> edges[], int n, int m, vector<ll>& mxdis, vector<bool>& isInNegativeCycle) {
    int i, j;

    for(i=0;i<n;i++) {
        for(j=0;j<m;j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            
            if(mxdis[u] != LONG_LONG_MAX && mxdis[v] > mxdis[u] + w)
                mxdis[v] = mxdis[u] + w;
        }
        // cout << i << " : ";
        // for(int k=1;k<=n;k++) {
        //     cout << mxdis[k] << " ";
        // }
        // cout << "\n";
    }

    // bool isInNegativeCycle[n+1] = {0};
    for(i=0;i<m;i++) { 
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if(mxdis[u] != LONG_LONG_MAX && mxdis[v] > mxdis[u] + w) {
            // cout << "-1\n";
            // return;
            // markNegativeCycles(isInNegativeCycle, edges, u, n);
            isInNegativeCycle[u] = 1;
        }
    }


    // cout << -mxdis[n] << "\n";
}

bool negativeCycleInPath(vector<int> adj[], int u, bool& didNegativeNodeOccured, bool vis[], vector<bool>& isInNegativeCycle) {

    // ps.push_back('\t');
    // cout << ps << u << " - " << didNegativeNodeOccured;
    didNegativeNodeOccured |= isInNegativeCycle[u];

    if(vis[u]) {
        // ps.pop_back();
        return didNegativeNodeOccured;
    }

    vis[u] = 1;
    for(int v : adj[u]) {
        // negativeCycleInPath(adj, v, didNegativeNodeOccured, vis, isInNegativeCycle, pathHaveNegativeCycle);
        if(negativeCycleInPath(adj, v, didNegativeNodeOccured, vis, isInNegativeCycle)) {
            // ps.pop_back();
            return 1;
        }
    }
    
    if(u == 1) {
        // ps.pop_back();
        // pathHaveNegativeCycle = didNegativeNodeOccured;
        return didNegativeNodeOccured;
    }

    // ps.pop_back();
    return 0;
}

int main()
{
    int i, j, n, m, q;
    cin >> n >> m;

    vector<ll> mxdis(n+1, LONG_LONG_MAX);
    vector<bool> isInNegativeCycle(n+1);
    mxdis[1] = 0;

    array<int,3> edges[m];
    vector<int> adj[n+1];
    for(i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;

        edges[i] = {u, v, -w};
        adj[v].push_back(u);
    }
    sort(edges, edges+n);

    bellmanFordMaxDistance(edges, n, m, mxdis, isInNegativeCycle);
    // for(i=0;i<n;i++) {
    //     cout << i << " : " << isInNegativeCycle[i] << " , ";
    // }
    // cout << "\n";
    bool vis[n+1] = {0};
    bool pathHaveNegativeCycle = 0;
    // negativeCycleInPath(adj, n, 0, vis, isInNegativeCycle, pathHaveNegativeCycle);
    if(negativeCycleInPath(adj, n, pathHaveNegativeCycle, vis, isInNegativeCycle)) {
        cout << "-1\n";
        return 0;
    }

    cout << -mxdis[n] << "\n";

    return 0;
}