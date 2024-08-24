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

    we just have to find Euler path, which we can do by Heirholtzer algorithm
    we would check that node 1 have 1 more outgoing edge, similarly
    we would check that node n have 1 more incoming edge
    after that, we would start heirholtzer algorithm from node 1

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

void dfs(vector<int> adj[], int u, int out[], vector<int>& path) {
    while(out[u]-- > 0) {
        dfs(adj, adj[u][out[u]], out, path);
    }
    path.push_back(u);
}

void printAdj(vector<int> adj[], int tn) {
    cout << "[\n";
    for(int i=0;i<tn;i++) {
        cout << "\t" << i << " : ";
        for(auto v : adj[i]) {
            cout << v << ", ";
        }
        cout << "\n";
    }
    cout << "]\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    vector<int> adj[n];
    int indeg[n]={0}, outdeg[n]={0};
    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }

    // printAdj(adj, n);

    for(i=0;i<n;i++) {
        // cout << i << " : " << indeg[i] << " , " << outdeg[i] << "\n";
        if(i == 0 && indeg[i]+1 != outdeg[i]) {
            // cout << "c1\n";
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        else if(i == n-1 && indeg[i] != outdeg[i]+1) {
            // cout << "c2\n";
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        else if(i > 0 && i < n-1 && indeg[i] != outdeg[i]) {
            // cout << "c3\n";
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> path;
    dfs(adj, 0, outdeg, path);
    for(i=0;i<n;i++) {
        if(outdeg[i] > 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    for(i=m;i>=0;i--) {
        cout << path[i]+1 << " ";
    }
    cout << "\n";

    return 0;

}