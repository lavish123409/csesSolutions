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

int main()
{
    int i, j, n, m;
    cin >> n >> m;

    vector<pair<int,int>> adj[n];
    for(i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        // adj[v].push_back({u, w});
    }

    // for(i=0;i<n;i++) {
    //     cout << i << " : ";
    //     for(auto [v, w] : adj[i]) {
    //         cout << "(" << v << " , " << w << ") - ";
    //     }
    //     cout << "\n";
    // }

    vector<ll> sdis(n, LONG_LONG_MAX);
    // sdis[0] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0, 0});

    while(!pq.empty()) {
        // printPQ(pq);
        ll dtu = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(sdis[u] > dtu) {
            sdis[u] = dtu;
            for(auto [v, w] : adj[u]) {
                pq.push({dtu + w, v});
            }
        }
    }

    for(i=0;i<n;i++) {
        cout << sdis[i] << " ";
    }
    cout << "\n";

    return 0;
}