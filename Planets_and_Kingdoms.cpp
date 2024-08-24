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

    brute force 
    - start form vertex 1, and store all the vertices which are reachable. We would give 1 kingdom to all vertices strongly connected to 1
    - check for every stored vertex whether, 1 is reachable or not
        - if it is reachable, give it kingdom 1
        - otherwise, for all vertices, which do not satisfy the connecting criteria or are still unvisted, start from step 1

    as, kingdom would be those vertices, from which every other vertex in the kingdom is reachable with directed teleporters(edges), we can call it as strongly connected components
    so, we can use kosaraju algorithm to find all SCCs

    kosaraju(adj):

        stack = []
        vis = []
        for every node in adj:
            if node is not visited:
                dfs(adj, node, vis, stack) // store the nodes in the stack according to their dfs end times

        tadj = transpose(adj)
        numberOfKingdoms = 1
        ans = []
        vis = []
        for node in stack:
            if node is not visited:
                dfs(tadj, node, vis, ans, numberOfKingdoms)
            stack.pop(node)

        print ans

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

void dfs(vector<int> adj[], int u, vector<bool>& vis, stack<int>& st) {
    if(vis[u]) {
        return;
    }

    vis[u] = 1;
    for(int v : adj[u]) {
        dfs(adj, v, vis, st);
    }

    st.push(u);
}

void reverseDfs(vector<int> adj[], int u, vector<bool>& vis, vector<int>& ans, int currentNumberOfKingdoms) {
    if(vis[u]) {
        return;
    }

    vis[u] = 1;
    ans[u] = currentNumberOfKingdoms;
    
    for(int v : adj[u]) {
        reverseDfs(adj, v, vis, ans, currentNumberOfKingdoms);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;
    vector<int> adj[n], tadj[n];

    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
        tadj[v].push_back(u);
    }

    // for(i=0;i<n;i++) {
    //     cout << i << ": ";
    //     for(int v : adj[i]) {
    //         cout << v << ", ";
    //     }
    //     cout << "\n";
    // }

    // for(i=0;i<n;i++) {
    //     cout << i << ": ";
    //     for(int v : tadj[i]) {
    //         cout << v << ", ";
    //     }
    //     cout << "\n";
    // }

    stack<int> st;
    vector<bool> vis(n);
    for(i=0;i<n;i++) {
        if(!vis[i]) {
            dfs(adj, i, vis, st);
        }
    }

    vector<int> ans(n);
    int currentNumberOfKingdoms = 0;

    vis = vector<bool>(n);
    while(!st.empty()) {
        int u = st.top();
        if(!vis[u]) {
            currentNumberOfKingdoms++;
            reverseDfs(tadj, u, vis, ans, currentNumberOfKingdoms);
        }
        st.pop();
    }

    cout << currentNumberOfKingdoms << "\n";
    for(int it : ans) {
        cout << it << " ";
    }
    cout << "\n";

    return 0;

}