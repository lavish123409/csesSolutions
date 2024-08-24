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

int main()
{
    int i, j, n, m;
    cin >> n >> m;

    vector<pair<int,int>> adj[n], adjn[n];
    array<int,3> edges[m];
    for(i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        adj[u].push_back({v, w});
        adjn[v].push_back({u, w});
        edges[i] = {u, v, w};
    }

    // for(i=0;i<n;i++) {
    //     cout << i << " : [ ";
    //     for(auto [v, w] : adj[i]) { 
    //         cout << v << " , " << w << " - ";
    //     }
    //     cout << "]\n";
    // }

    vector<ll> mxdis1(n, LONG_LONG_MAX);
    // vector<pair<int,int>> parww(n, {-1, 0});
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> mnq;

    mxdis1[0] = 0;
    mnq.push({0, 0});

    while(!mnq.empty()) {
        ll cdis = mnq.top().first;
        int u = mnq.top().second;
        // cout << cdis << " : " << u << "\n";
        mnq.pop();

        if(cdis > mxdis1[u]) {
            continue;
        }
        // cout << "yo1\n";

        if(u == n-1) {
            break;
        }
        // cout << "yo2\n";

        for(auto [v, w] : adj[u]) {
            // cout << v << " - " << w << " , ";
            if(mxdis1[v] > mxdis1[u] + w) {
                mxdis1[v] = mxdis1[u] + w;
                mnq.push({mxdis1[u] + w, v});
                // parww[v] = {u, w};
            }
        }
        // cout << "\n";

    }

    // for(i=0;i<n;i++) {
    //     cout << mxdis1[i] << " ";
    // }
    // cout << "\n";

    vector<ll> mxdisn(n, LONG_LONG_MAX);
    // vector<pair<int,int>> parww(n, {-1, 0});
    // priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> mnq;

    mxdisn[n-1] = 0;
    mnq.push({0, n-1});

    while(!mnq.empty()) {
        ll cdis = mnq.top().first;
        int u = mnq.top().second;
        // cout << cdis << " : " << u << "\n";
        mnq.pop();

        if(cdis > mxdisn[u]) {
            continue;
        }
        // cout << "yo1\n";

        if(u == 0) {
            break;
        }
        // cout << "yo2\n";

        for(auto [v, w] : adjn[u]) {
            // cout << v << " - " << w << " , ";
            if(mxdisn[v] > mxdisn[u] + w) {
                mxdisn[v] = mxdisn[u] + w;
                mnq.push({mxdisn[u] + w, v});
                // parww[v] = {u, w};
            }
        }
        // cout << "\n";

    }
    // for(i=0;i<n;i++) {
    //     cout << mxdisn[i] << " ";
    // }
    // cout << "\n";

    ll ans = LONG_LONG_MAX;
    for(i=0;i<m;i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        if(mxdis1[u] != LONG_LONG_MAX && mxdisn[v] != LONG_LONG_MAX ) {
            ans = min(ans, mxdis1[u] + mxdisn[v] + w / 2);
        }
    }

    cout << ans << "\n";

    // for(i=0;i<n;i++) {
        // cout << mxdis1[i] << " ";
    // }
    // cout << "\n";

    // int tn = n-1;
    // int mxwt=0;
    // while(tn != 0) {
    //     mxwt = max(mxwt, parww[tn].second);
    //     tn = parww[tn].first;
    // }
    // // cout << "mxwt: " << mxwt << "\n";

    // cout << mxdis1[n-1] - ((mxwt + 1) / 2);
    return 0;
}