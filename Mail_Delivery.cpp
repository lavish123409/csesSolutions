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

    we know a graph is Eularian, if for every vertex, if we can enter that vertex in n ways then we should be able to exit it in n ways
    for undirected graph, degree of vertex should be even
    for directed graph, indegree of vertex should be equal to outdegree

    I approach - to print eularian cycle
    after coming to any vertex, we would see if any outgoing edge is not used or visited yet
    we would use it and mark it as used
    or, we can just remove that edge after traversing it

    problem1 - as we are taking edges randomly, so we can end up in starting vertex without visiting all the edges
    for ex, in graph 
    1 2
    2 3
    2 4
    3 4
    4 2
    4 1
    if starting vertex is 1, we can directly go to 1 from 4 (path: 1->2->3->4->1) without visiting 2->4 and 4->2

    to address, this problem we would put every edge incoming to starting vertex separately,i.e, all nodes previous to starting vertex, and use those edges only when previous nodes have exhausted all of there outgoing edges
    problem1.1 - in this previous nodes solution
    for ex, in graph 
    1 2
    2 3
    2 4
    3 4
    4 2
    4 5
    5 1
    now, previous nodes is 5 and there is no outgoing edge from 5 other than to 1, so we can traverse it without visiting 2->4 and 4->2

    Realisation - question is asking to find eulerian cycle on undirected graph
    not much effect, multiple edges and self loops would still be there

    Solution
    Fluery algo - visit only those edges at any vertex which are not a bridge first, and the bridge one at last
    Heirholzer algo - keep following unused edges and removing them until we get stuck. Once we get stuck, we backtrack to the nearest vertex in our current path that has unused edges, and we repeat the process until all the edges have been used. 

    Heir

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

void dfs(set<int> adj[], int u, int deg[], vector<int> &path) {
    while(deg[u] > 0) {
        int v = *adj[u].begin();
        
        adj[u].erase(v);
        adj[v].erase(u);
        deg[u]--;
        deg[v]--;

        dfs(adj, v, deg, path);
    }

    path.push_back(u);
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    set<int> adj[n];
    int deg[n] = {0};
    while(m--) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].insert(v);
        adj[v].insert(u);
        deg[u]++;
        deg[v]++;
    }

    for(i=0;i<n;i++) {
        if(deg[i]&1) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> path;
    dfs(adj, 0, deg, path);

    for(i=0;i<n;i++) {
        if(deg[i] > 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for(int node : path) {
        cout << node+1 << " ";
    }
    cout << "\n";

    return 0;

}