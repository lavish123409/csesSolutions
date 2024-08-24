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
    we can see that every node would be either in the cycle or not, for cycle nodes any distance would end up in cycle
    - store whether current node is in cycle and its cycle length in an array
    - input node and k, number of teleportation to do
    - while k is not 0 and current node is not in cycle, decrease k and teleport
    - if k is 0, return current node
    - if current node is in cycle, do k = k % cycleLength and repeat from step 3

    how to get nodes which are in cycle?
        - do dfs and mark those nodes which lead to a cycle
        - reverse the adjacency list, and repeat above step
        - those nodes would be in the cycle which are marked in both

    TLE1 - probably I am doing too many dfs

    YT solution - binary lifting
    we can find kth ancestor of a node in tree in logk steps, here parent is like the next node

    - make a 2D array of n * logn, where for each node its 2^j th ancestor would be stored at [node][j]
    - k = 2^a1 + 2^an, so we can take first 2^an ancestor of node and then take its 2^a1 ancestor, which would be our kth ancestor
    
*/

bool dfsForCycle(int adj[], int u, vector<bool>& vis, vector<bool>& currStack, vector<bool>& isNodeInCycle) {
    if(currStack[u]) {
        return 1;
    }

    if(vis[u]) {
        return 0;
    }

    vis[u] = 1;
    currStack[u] = 1;
    isNodeInCycle[u] = dfsForCycle(adj, adj[u], vis, currStack, isNodeInCycle);

    currStack[u] = 0;
    return 0;
}

void getLengthOfCycle(int adj[], int u, vector<pair<bool,int>>& isCycleNode, int& length) {
    if(!isCycleNode[u].first) {
        return;
    }

    length++;
    getLengthOfCycle(adj, adj[u], isCycleNode, length);
    // isCycleNode[u].second = length;
}

void getNodesInCycle(int adj[], int radj[], vector<pair<bool,int>>& isNodeInCycle, int n) {
    int i;
    vector<bool> vis(n+1), currStack(n+1);
    vector<bool> forwardPass(n+1), backwardPass(n+1);
    for(i=1;i<=n;i++) {
        if(!vis[i]) {
            dfsForCycle(adj, i, vis, currStack, forwardPass);
        }
    }

    vis = vector<bool>(n+1);
    for(i=1;i<=n;i++) {
        if(!vis[i]) {
            dfsForCycle(radj, i, vis, currStack, backwardPass);
        }
    }

    for(i=1;i<=n;i++) {
        isNodeInCycle[i].first = forwardPass[i] & backwardPass[i];
    }

    for(i=1;i<=n;i++) {
        if(isNodeInCycle[i].first && !isNodeInCycle[i].second)
            getLengthOfCycle(adj, i, isNodeInCycle, isNodeInCycle[i].second);
    }
}

const int MAXN = 2e5+5;
const int MAXD = 30;
int anc[MAXN][MAXD];

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int n, m, i;
    cin >> n >> m;

    // int adj[n+1], radj[n+1];

    // for(i=1;i<=n;i++) {
    //     int x;
    //     cin >> x;

    //     adj[i] = x;
    //     radj[x] = i;
    // }

    // vector<pair<bool,int>> isNodeInCycle(n+1);
    // getNodesInCycle(adj, radj, isNodeInCycle, n);

    // while(m--) {
    //     int u, k;
    //     cin >> u >> k;

    //     while(k--) {
    //         u = adj[u];
    //         if(isNodeInCycle[u].first) {
    //             k %= isNodeInCycle[u].second;
    //         }
    //     }

    //     cout << u << "\n";
    // }

    // int logn = log2(n) + 1;
    // int logn = 30;
    // int anc[n+1][logn];
    // int anc[int(2e5+1)][32];
    // vector<vector<int>> anc(n+1, vector<int>(logn));

    // memset(anc, 0, sizeof(anc));

    for(i=1;i<=n;i++) {
        cin >> anc[i][0];
    }

    // for(int j=1;j<logn;j++) {
    for(int j=1;j<MAXD;j++) {
        for(i=1;i<=n;i++) {
            anc[i][j] = anc[anc[i][j-1]][j-1];
        }
    }

    // for(i=1;i<=n;i++) {
    //     cout << i << " : ";
    //     for(int j=0;j<logn;j++) {
    //         cout << anc[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    while(m--) {
        int u, k;
        cin >> u >> k;

        int bt = 0;
        // while((uint32_t)(1 << bt) <= k) {
        //     if((uint32_t)(1 << bt) & k) {
        //         u = anc[u][bt];
        //     }
        //     bt++;
        //     // cout << bt << " : " << (uint32_t)(1 << bt) << "\n";
        // }
        while((1 << bt) <= k) {
            if((1 << bt) & k) {
                u = anc[u][bt];
            }
            bt++;
            // cout << bt << " : " << (uint32_t)(1 << bt) << "\n";
        }

        cout << u << "\n";
    }

    return 0;

}