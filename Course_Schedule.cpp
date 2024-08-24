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

    do bfs with all vertices whose inedge is 0

    if b depends on a => a -> b

    Kahn's algo

    queue q
    put all vertices in q whose inedge is 0
    ans = []

    while q is not empty:
        u = q.front()
        ans.push_back(u)

        for all neighbors v of u:
            if inedge[v] > 0:
                inedge[v]--
                if inedge[v] == 0:
                    q.push(v)

    for all vertices u:
        if inedge[u] != 0:
            print IMPOSSIBLE

    print all vertices in ans
    
*/
void bfsKahnsAlgorithm(vector<int> adj[], int n, vector<int>& inedge) {
    queue<int> q;

    int i;
    for(i=0;i<n;i++) {
        if(!inedge[i]) {
            q.push(i);
        }
    }

    vector<int> ans;
    while(!q.empty()) {
        int u = q.front();
        ans.push_back(u);
        q.pop();

        for(int v : adj[u]) {
            if(inedge[v] > 0) {
                inedge[v]--;
                if(!inedge[v]) {
                    q.push(v);
                }
            }
        }
    }

    for(i=0;i<n;i++) {
        if(inedge[i] > 0) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }

    for(int v : ans) {
        cout << v+1 << " ";
    }
    cout << "\n";
}

/*

    do dfs for all vertices whose inedge is 0

    if cycle is found at any vertex print IMPOSSIBLE

    other wise, put vertex in stack after all its neighbors have been visited

    dfs(adj, u):
        if u is currStack:
            return 1

        if u is visited:
            return 0

        vis[u] = 1
        currStack[u] = 1
        for all neighbors v of u:
            if dfs(adj, v):
                return 1

        currStack[u] = 0
        stack.push(u)

        return 0

    for all vertices u whose inedge[u] is 0:
        if dfs(adj, i):
            print IMPOSSIBLE

    while stack is not empty:
        print top of stack
        remove top of stack

        

*/

bool isDFSCycle(vector<int> adj[], int u, vector<bool>& vis, vector<bool>& currStack, stack<int>& topSort) {
    if(currStack[u]) {
        return 1;
    }

    if(vis[u]) {
        return 0;
    }

    vis[u] = 1;
    currStack[u] = 1;
    for(int v : adj[u]) {
        if(isDFSCycle(adj, v, vis, currStack, topSort)) {
            return 1;
        }
    }

    currStack[u] = 0;
    topSort.push(u);

    return 0;

}

int main()
{
    int n, m, i;
    cin >> n >> m;

    vector<int> adj[n], inedge(n);

    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        if(u == v) continue;
        adj[u].push_back(v);
        inedge[v]++;
    }

    // for(i=0;i<n;i++) {
    //     cout << i << " : ";
    //     for(int v : adj[i]) {
    //         cout << v << " ";
    //     }
    //     cout << "\n";
    // }

    // bfsKahnsAlgorithm(adj, n, inedge);

    stack<int> topSort;
    vector<bool> vis(n), currStack(n);
    for(i=0;i<n;i++) {
        if(inedge[i] == 0 && !vis[i] && isDFSCycle(adj, i, vis, currStack, topSort)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    if(int(topSort.size()) != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    while(!topSort.empty()) {
        cout << topSort.top()+1 << " ";
        topSort.pop();
    }
    cout << "\n";
    return 0;

}