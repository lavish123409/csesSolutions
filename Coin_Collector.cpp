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

    from the question, we can observe that we can visit some vertex any number of times but can take its coins only once
    so, we can take all the coins in a SCC and move to next SCC and then, take all its coins(recursively)
    so, we can form dag from total graph using its SCCs
    and find the the path with maximum coins in that DAG

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

void dfs(vector<int> adj[], int u, vector<bool> &vis, vector<int> &order) {
    vis[u] = 1;
    for(int v : adj[u]) {
        if(!vis[v]) {
            dfs(adj, v, vis, order);
        }
    }

    order.push_back(u);
}

void dfsRev(vector<int> adj[], int u, vector<bool> &vis, int sccIndex, int sccNo[]) {
    vis[u] = 1;
    sccNo[u] = sccIndex;

    for(int v : adj[u]) {
        if(!vis[v]) {
            dfsRev(adj, v, vis, sccIndex, sccNo);
        }
    }
}

ll findMaxPath(set<int> adj[], int u, vector<ll> &dp, vector<ll> &weight) {
    if(dp[u] != -1) {
        return dp[u];
    }

    dp[u] = 0;
    for(int v : adj[u]) {
        dp[u] = max(dp[u], findMaxPath(adj, v, dp, weight));
    }

    dp[u] += weight[u];
    return dp[u];
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    int k[n];
    for(i=0;i<n;i++) {
        cin >> k[i];
    }

    vector<int> adj[n], adjT[n];
    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
        adjT[v].push_back(u);
    }

    vector<int> finTime;
    vector<bool> vis(n);
    for(i=0;i<n;i++) {
        if(!vis[i]) {
            dfs(adj, i, vis, finTime);
        }
    }
    // for(i=0;i<n;i++) {
    //     cout << finTime[i] << " : ";
    // }
    // cout << "\n";

    int totalSCCs = 0;
    int sccNo[n];
    memset(sccNo, -1, sizeof(sccNo));
    vis = vector<bool>(n);

    for(i=n-1;i>=0;i--) {
        // cout << ~i << "\n";
        int u = finTime[i];
        // cout << u << "\n";
        if(!vis[u]) {
            dfsRev(adjT, u, vis, totalSCCs++, sccNo);
        }
    }
    // cout << totalSCCs << " <- tscc\n";

    vector<ll> sumOfSCC(totalSCCs);
    set<int> dag[totalSCCs];
    for(i=0;i<n;i++) {
        sumOfSCC[sccNo[i]] += k[i];
    }

    for(i=0;i<n;i++) {
        for(int v : adj[i]) {
            if(sccNo[i] != sccNo[v] && !dag[sccNo[i]].count(sccNo[v])) {
                dag[sccNo[i]].insert(sccNo[v]);
            }
        }
    }

    // for(i=0;i<n;i++) {
    //     cout << sccNo[i] << " - ";
    // }
    // cout << "\n";
    // for(i=0;i<totalSCCs;i++) {
    //     cout << i << " : ";
    //     for(int v : dag[i]) {
    //         cout << v << " , ";
    //     }
    //     cout << "\n";
    // }

    vector<ll> maxPath(totalSCCs, -1);
    // vector<bool> vis(totalSCCs);

    for(i=0;i<totalSCCs;i++) {
        if(maxPath[i] == -1) {
            findMaxPath(dag, i, maxPath, sumOfSCC);
        }
    }
    // for(i=0;i<totalSCCs;i++) {
    //     cout << maxPath[i] << " ";
    // }
    // cout << "\n";

    cout << *max_element(maxPath.begin(), maxPath.end()) << "\n";
    return 0;

}