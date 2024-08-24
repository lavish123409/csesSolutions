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

/*

    brute force would be to
    start from node 1, and visit all adjacent nodes
    keep visiting all nodes if it is not visited, and check in visited array whether all nodes are covered
    if it is, then increment the counter
    otherwise, backtrack since all the nodes are visited
    O(n!)

    we can use dp to prevent solving subproblems again
    use n-length bitmask to represent visited for nodes
    when coming to any vertex, make it visited in bitmask
    traverse all adjacent nodes, if they are not visted
    if mask is full, increment counter and return
    store it in dp[nodes][mask], mask = 2^n
    O(n * 2^n)

    WA/TLE1 - did not realised that in the question, it is asked to only go from node 1 to n covering all other nodes
              my code was ending at any node, covering all nodes

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

int dfs(vector<int> adj[], int u, int mask, int n, vector<vector<int>> &dp) {
    if(u == n-1 && mask == ((1 << n) - 1)) {
        // cout << "yo\n";
        return 1;
    }

    if(u == n-1 || mask == ((1 << n) - 1)) {
        // cout << "yo\n";
        return 0;
    }

    if(dp[u][mask] != -1) {
        return dp[u][mask];
    }

    // ps.push_back('\t');

    // mask |= (1 << u);
    // cout << ps << u << " : " << bitset<4>(mask) << " = " << bitset<4>((1 << n) - 1) << " :: " << (mask == ((1 << n) - 1));
    int ans = 0, mod = int(1e9+7);
    for(int v : adj[u]) {
        if(!((1 << v) & mask)) {
            ans = (1ll * ans + dfs(adj, v, mask | (1 << v), n, dp)) % mod;
            // cout << ps << v << " - " << bitset<4>(mask) << "\n";
        }
    }
    // cout << ps << ans;
    // mask &= ~(1 << u);
    // ps.pop_back();

    return dp[u][mask] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    vector<int> adj[n];
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));
    int mask = 1;

    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
    }
    
    cout << dfs(adj, 0, mask, n, dp) << "\n";

    return 0;

}