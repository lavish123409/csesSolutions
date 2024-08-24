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

    I approach
    do dfs with dp
    store 1 + max distance to destination from all neighbor vertices

    dfs(adj, u, parent):

        if current node u is destination:
            return 1

        if current node is visted:
            return dp[u]

        ans = -1
        for all neighbors v of u in adj:
            // ans = max(ans, 1 + dfs(adj, v))
            if ans < 1 + dfs(adj, v, parent):
                ans = 1 + dfs(adj, v, parent)
                parent[v] = u

        return dp[u] = ans

    WA 1  - answer not correct, if last node is not reachable, if all neighbors do not have path to last node, current node also does not have a path
    TLE 1 - dp would not be effective if ans is also -1 for node if last node is unreachable from current node
    WA 2  - parent of a node would be initialized based on which parent would come later, change of approach
            ex- 7 8
                4 7
                1 2
                2 5
                1 3
                3 4
                4 5
                5 6
                6 7


    II approach
    BFS
    - initialize parent of every neighbor vertex with current vertex
    - for every node its parent would be that parent whose level is highest

    TLE 1 - failing for this type of test case
            1 -> 2, 1 -> 2
            it would add 2 two times to the queue, and if same happens for 3, it would be added 4 times, leading to addition of vertices exponentially


    III approach
    topologial sorting

    do topological sorting of only those vertices which lie on the path from source to vertex

    dfs(adj, u, dp):

        if u is destination:
            return 1

        if u is visited:
            return dp[u]

        canReachToDestination = 0
        vis[u] = 1
        for all neighbors v of u in adj:
            canReachToDestination |= dfs(adj, v)

        if canReachToDestination:
            stack.push(u)

        return dp[u] = canReachToDestination

    Failing on given test case
    5 5
    1 2
    2 5
    1 3
    3 4
    4 5

    it is printing 2 also which would come in topological sort, but not in the longest path

    I approach
    earlier one is better, just instead of storing parent, store best child for every node and traverse from 1st node to last node    

    
*/

// int dfs(vector<int> adj[], int u, int dst, vector<int>& dp, vector<int>& parent) {

//     if(u == dst) {
//         return 1;
//     }

//     if(dp[u] != 0) {
//         return dp[u];
//     }

//     int ans = -1;
//     for(int v: adj[u]) {
//         int cans = 1 + dfs(adj, v, dst, dp, parent);
//         if(cans > 0 && ans < cans) {
//             ans = cans;
//             parent[v] = u;
//         }
//     }

//     return dp[u] = ans;
// }

// bool dfs(vector<int> adj[], int u, int dest, vector<int>& dp, stack<int>& topSort) {
//     if(u == dest) {
//         return 1;
//     }

//     if(dp[u] != -1) {
//         return dp[u];
//     }

//     dp[u] = 0;
//     for(int v : adj[u]) {
//         dp[u] |= dfs(adj, v, dest, dp, topSort);
//     }

//     if(dp[u]) {
//         topSort.push(u);
//     }

//     return dp[u];
// }

int dfs(vector<int> adj[], int u, int dst, vector<int>& dp, vector<int>& child) {

    if(u == dst) {
        return 1;
    }

    if(dp[u] != 0) {
        return dp[u];
    }

    int ans = -1;
    for(int v: adj[u]) {
        int cans = 1 + dfs(adj, v, dst, dp, child);
        if(cans > 0 && ans < cans) {
            ans = cans;
            child[u] = v;
        }
    }

    return dp[u] = ans;
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

    // vector<int> parent(n, -1), dp(n);
    // int ans = dfs(adj, 0, n-1, dp, parent);

    // for(int it : parent) {
    //     cout << it << " , ";
    // }
    // cout << "\n";
    
    // for(int it : dp) {
    //     cout << it << " , ";
    // }
    // cout << "\n";

    // if(ans == -1) {
    //     cout << "IMPOSSIBLE\n";
    //     return 0;
    // }

    // int currentNode = n-1;
    // vector<int> path;
    // while(currentNode != -1) {
    //     path.push_back(currentNode);
    //     currentNode = parent[currentNode];
    // }

    // reverse(path.begin(), path.end());

    // cout << ans << "\n";
    // for(int node : path) {
    //     cout << node+1 << " ";
    // }
    // cout << "\n";

    // vector<int> parent(n, -1);
    // queue<int> q;
    // q.push(0);

    // while(!q.empty()) {
    //     int u = q.front();
    //     q.pop();

    //     for(int v : adj[u]) {
    //         q.push(v);
    //         parent[v] = u;
    //     }
    // }

    // if(parent[n-1] == -1) {
    //     cout << "IMPOSSIBLE\n";
    //     return 1;
    // }

    
    // int currentNode = n-1;
    // vector<int> path;
    // while(currentNode != -1) {
    //     path.push_back(currentNode);
    //     currentNode = parent[currentNode];
    // }

    // reverse(path.begin(), path.end());

    // cout << path.size() << "\n";
    // for(int node : path) {
    //     cout << node+1 << " ";
    // }
    // cout << "\n";

    // stack<int> topSort;
    // vector<int> dp(n, -1);

    // if(!dfs(adj, 0, n-1, dp, topSort)) {
    //     cout << "IMPOSSIBLE\n";
    //     return 1;
    // }

    // cout << topSort.size() << "\n";
    // while(!topSort.empty()) {
    //     cout << topSort.top() + 1 << " ";
    //     topSort.pop();
    // }
    // cout << "\n";

    vector<int> child(n, -1), dp(n);
    int ans = dfs(adj, 0, n-1, dp, child);

    // for(int it : child) {
    //     cout << it << " , ";
    // }
    // cout << "\n";
    
    // for(int it : dp) {
    //     cout << it << " , ";
    // }
    // cout << "\n";

    if(ans == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    int currentNode = 0;
    vector<int> path;
    while(currentNode != -1) {
        path.push_back(currentNode);
        currentNode = child[currentNode];
    }

    // reverse(path.begin(), path.end());

    cout << ans << "\n";
    for(int node : path) {
        cout << node+1 << " ";
    }
    cout << "\n";

    return 0;

}