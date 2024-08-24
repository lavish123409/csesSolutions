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

int getNodeInNegativeCycle(vector<array<int, 2>> adj[], vector<bool>& haveIncomingEdge, int n) {
    vector<int> mndis(n, INT_MAX);

    int i, u;
    mndis[0] = 0;
    for(i=0;i<n;i++) {
        if(!haveIncomingEdge[i]) {
            mndis[i] = 0;
        }
        cout << i << " : " << mndis[i] << " , ";
    }
    for(i=0;i<n-1;i++) {
        for(u=0;u<n;u++) {
            for(auto [v, w] : adj[u]) {
                if(mndis[u] != INT_MAX) {
                    mndis[v] = min(mndis[v], mndis[u] + w);
                }
            }
        }
    }

    for(u=0;u<n;u++) {
        for(auto [v, w] : adj[u]) {
            if(mndis[u] != INT_MAX && mndis[v] > mndis[u] + w) {
                return v;
            }
        }
    }

    return -1;
}

bool getCycle(vector<array<int,2>> adj[], int u, vector<bool>& currStack, vector<int>& ans) {
    if(currStack[u]) {
        return 1;
    }

    currStack[u] = 1;
    ans.push_back(u);
    for(auto [v, w] : adj[u]) {
        if(getCycle(adj, v, currStack, ans)) {
            return 1;
        }
    }

    ans.pop_back();
    return 0;
}

bool getNegativeCycle(vector<array<int,2>> adj[], int u, vector<bool>& vis, vector<bool>& currStack, map<int, int>& pathSum, vector<int>& currPath, int currSum) {
    if(vis[u]) {
        if(!currStack[u]) {
            return 0;
        }

        if(currSum - pathSum[u] < 0) {
            cout << "YES\n";
            bool didPreviousNodeCame = 0;
            for(int it : currPath) {
                if(it == u) {
                    didPreviousNodeCame = 1;
                }
                if(didPreviousNodeCame) {
                    cout << it+1 << " ";
                }
            }
            cout << u+1 << "\n";
            return 1;
        }

        return 0;
    }

    vis[u] = 1;
    currStack[u] = 1;
    pathSum[u] = currSum;
    currPath.push_back(u);

    for(auto [v, w] : adj[u]) {
        if(getNegativeCycle(adj, v, vis, currStack, pathSum, currPath, currSum + w)) 
            return 1;
    }

    vis[u] = 0;
    currStack[u] = 0;
    pathSum.erase(u);
    currPath.pop_back();

    return 0;
}

/*
    spfa() {
        // if some vertex is relaxed, then only put it in queue
        while(q not empty) {
            u = q.top()
            inQ[u] = false

            for (v, w in adj[u]) {
                if(dis[v] > dis[u] + w) {

                }
            }
        }
    }
*/

int main()
{
    int i, j, n, m;

    cin >> n >> m;

    vector<array<int,3>> edges(m);
    for(i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        edges[i] = {u, v, w};
    }

    vector<ll> mndis(n), par(n, -1);
    int x = -1;
    for(i=0;i<n;i++) {
        x = -1;
        for(j=0;j<m;j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];

            if(mndis[v] > mndis[u] + w) {
                mndis[v] = mndis[u] + w;
                par[v] = u;
                x = v;
            }
        }
    }

    if(x == -1) {
        cout << "NO\n";
        return 0;
    }

    for(i=0;i<n-1 && par[x] != -1;i++) {
        x = par[x];
    }

    // cout << "x: " << x << "\n";
    vector<int> ans;
    int v = x;
    do {
        ans.push_back(v);
        v = par[v];
    } while(v != x);

    reverse(ans.begin(), ans.end());

    cout << "YES\n";
    for(int it : ans) {
        cout << it+1 << " ";
    }
    cout << ans[0]+1 << "\n";
    return 0;

}