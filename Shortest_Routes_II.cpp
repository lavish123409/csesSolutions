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
    int i, j, n, m, q;
    cin >> n >> m >> q;

    ll adjm[n][n];
    memset(adjm, -1, sizeof(adjm));
    for(i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        if(adjm[u][v] != -1) {
            adjm[u][v] = min(adjm[u][v] , 1ll * w);
        }
        else {
            adjm[u][v] = w;
        }
        adjm[v][u] = adjm[u][v];
        adjm[u][u] = 0;
        adjm[v][v] = 0;
        // adj[v].push_back({u, w});
    }

    int imn, u, v;
    for(imn=0;imn<n;imn++) {
        for(u=0;u<n;u++) {
            for(v=0;v<n;v++) {
                if(adjm[u][imn] != -1 && adjm[imn][v] != -1 && (adjm[u][v] == -1 || adjm[u][imn] + adjm[imn][v] < adjm[u][v])) {
                    adjm[u][v] = adjm[u][imn] + adjm[imn][v];
                    adjm[v][u] = adjm[u][v];
                }
            }
        }
    }

    // for(i=0;i<n;i++) {
    //     for(j=0;j<n;j++) {
    //         cout << adjm[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    while(q--) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        cout << adjm[u][v] << "\n";
    }

    return 0;
}