#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int dp[int(1e5+1)];

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

/*

    I approach
    do dfs with dp
    dp[v] - how many ways we can reach n from v

    dfs(adj, u, dp):
        if u is visited:
            return dp[u]

        dp[u] = 0
        for all neighbors v in adj[u]:
            dp[u] += dfs(adj, v, dp)

        return dp[u]
    
*/

int dfs(vector<int> adj[], int u, int n) {

    if(u == n-1) {
        return 1;
    }

    if(dp[u] != -1) {
        return dp[u];
    }

    dp[u] = 0;
    for(int v : adj[u]) {
        dp[u] = (dp[u] + dfs(adj, v, n)) % int(1e9+7);
    }

    return dp[u];
}

int main()
{
    int n, m, i;
    cin >> n >> m;

    vector<int> adj[n];

    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        if(u == v) continue;
        adj[u].push_back(v);
    }

    memset(dp, -1, sizeof(dp));
    cout << dfs(adj, 0, n) << "\n";

    return 0;

}