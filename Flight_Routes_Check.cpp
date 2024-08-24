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
    using DSU
    we know that using DSU, we can find number of components, and if number of components
    - is 1, we can print yes, as we can reach any node from another node in same component
    - is >1, we can print the representative of any 2 nodes, whose representatives (depicted their components) are different

    problem - didn't realized that it is  adirected graph for which the DSU would not work, because joining 2 vertices u and v in DSU means we can reach v from u and u from v, which is not true in case of directed graph

    II approach
    using kosaraju algorithm
    we can find number of strongly connected components(SCCs) using kosaraju algorithm, so as soon as we would find 2 component using kosaraju algorithm, we would print 1st node in transposed graph and current node

    - do dfs, and store all vertices after we have visited all its neighbors (storing vertices according to their dfs end times) // we would not need it, because first vertex would be the one which would end last
    - transpose the graph
    - do dfs in reverse order of stored vertices (there is only first vertex) and store the first vertex, after doing dfs
        - if we encounter any vertex unvisited, it is part of other component, so print this and first vertex
        - if we visit all the vertices, there is only 1 component

    kosaraju(adj);

        vis = []
        dfs(adj, 1, vis)

        for node in adj:
            if node is not visited:
                print node, 1
                return

        transposeAdj = transpose(adj)

        vis = []
        dfs(1, transposeAdj, vis)

        for node in adj:
            if node is not visited:
                print node, 1
                return

        print YES

    WA1 - was inputting edges from 0 to n and not 0 to m
    also was confused about this test case
    1 2
    2 1
    1 3
    3 1

    I was thinking that 2 cannot reach 3 because there is no edge from 2 to 3 and kosaraju algorithm would consider them in 1 component as both are reachable from 1 in normal and transpose graph
    but it is wrong because component means that we can reach any vertex from any other vertex, which is true because we can reach 3 from 2 via and vice versa

    Essence of kosaraju algorithm-
    if some vertices are reachable from some node, it can happen that this node might not be reachable from those nodes, so if we would reverse all the edges and still those nodes are reachable, it means this node is also reachable from those nodes, hence the connectivity

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];


void dfs(vector<int> adj[], int u, vector<bool>& vis) {
    if(vis[u]) {
        return;
    }

    vis[u] = 1;
    for(int v:  adj[u]) {
        dfs(adj, v, vis);
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

    vector<bool> vis(n);
    dfs(adj, 0, vis);

    for(i=0;i<n;i++) {
        if(!vis[i]) {
            cout << "NO\n";
            cout << "1 " << i+1 << "\n";
            return 0;
        }
    }

    vis = vector<bool>(n);
    dfs(tadj, 0, vis);

    for(i=0;i<n;i++) {
        if(!vis[i]) {
            cout << "NO\n";
            cout << i+1 << " 1" << "\n";
            return 0;
        }
    }

    cout  << "YES\n";

    return 0;

}