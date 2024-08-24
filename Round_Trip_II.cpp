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
    // bool isCycledfs(adj, u, vis, currStack, par, cycle)

    if u is in currStack:
        tempNode = u
        do:
            cycle.push_back(tempNode)
            tempNode = par[tempNode]
        while tempNode != u
        cycle.push_back(u)
        return 1

    if u is visited:
        return 0

    vis[u] = 1
    currStack[u] = 1
    for all v in adj[u]:
        par[v] = u
        if(isCycledfs(adj, v, vis, currStack)):
            return 1
    
    currStack[u] = 0
            
*/

bool isCycleDFS(vector<int> adj[], int u, vector<bool>& vis, int par[], vector<int>& cyclePath) {

    ps.push_back('\t');
    cout << ps << u;
    cout << ps;
    for(int i=0;i<vis.size();i++) {
        cout << par[i] << " , ";
    }


    // if(par[u]) {
    //     // We found cycle
    //     // int n = vis.size();
    //     // for(int i=0;i<n;i++) {
    //     //     cout << par[i] << " ";
    //     // }
    //     int tempNode = u;
    //     do {
    //         cyclePath.push_back(tempNode);
    //         tempNode = par[tempNode];
    //     } while(tempNode != u);
    //     cyclePath.push_back(u);

    //     return 1;
    // }

    if(vis[u]) {
        ps.pop_back();
        return 0;
    }

    vis[u] = 1;
    // currStack[u] = 1;
    for(int v : adj[u]) {
        cout << ps << "v: " << v;
        if(par[v] != -1) {
            cout << ps << "inc";
            int tempNode = v;
            do {
                cyclePath.push_back(tempNode);
                tempNode = par[tempNode];
            } while(tempNode != v);
            cyclePath.push_back(v);
            ps.pop_back();
            return 1;
        }
        else {
            par[v] = u;
            if(isCycleDFS(adj, v, vis, par, cyclePath)) {
                ps.pop_back();
                return 1;
            }
            par[v] = -1;
        }
    }
    // par[u] = -1;

    ps.pop_back();
    // currStack[u] = 0;
    return 0;
}

void dfs(vector<int> adj[], int n) {

    vector<bool> vis(n), currStack(n);
    int par[n];
    vector<int> cyclePath;

    memset(par, -1, sizeof(par));
    for(int i=0;i<n;i++) {
        if(!vis[i] && isCycleDFS(adj, i, vis, par, cyclePath)) {
            reverse(cyclePath.begin(), cyclePath.end());
            cout << cyclePath.size() << "\n";
            for(int u : cyclePath) {
                cout << u+1 << " ";
            }
            cout << "\n";
            return;
        } 
    }
    cout << "IMPOSSIBLE\n";

}

/*

    // bfs
    

*/

void bfs(vector<int> adj[], int n) {



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

    for(i=0;i<n;i++) {
        cout << i << " : ";
        for(int v : adj[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }

    dfs(adj, n);
    return 0;

}