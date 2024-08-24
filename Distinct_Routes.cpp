#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

template<typename T>
void printa(T a[], int l, int r) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(a[i]); cerr << "}]\n";}

#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#else
#define debug(x...)
#define debuga(x, l, r)
#endif


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

    I am thinking that we can perform the max flow algo and then whichever would have 0 residual flow from source to sink
    then it means current flow is passing through that path, or in question's words - we can use those teleporters path

    Q. What would happen if edges were weighted and we had to find the paths?
    A. I think if edges were weighted, then it does not make sense to choose some path over other. Meaning is that flow would not completly stop in an edge
    unless no flow is coming towards it. In that case, I think we would have to store all paths corresponding to the edges and whenever we would find a negative flow (-f) in some edge, then we would have to decrease f paths which contain that edge
    For ex, suppose this the graph where 1 is source and 4 is sink
    1 2 10
    2 3 5
    3 4 7
    ....

    Now, we can have 5 paths of 1->2->3->4 because of 2-3 edge's bottleneck
    but if we would get -2 flow in 2-3 edge, then we would have to remove 2 paths of 1->2->3->4 because the flow is 3 now from 2-3 edge

    WA1 - it might be taking reverse edges which have capacity or residual flow as 0

    WA2 - bug in implementation of dfs, what if some node occurs in 2 paths
    For ex, take this graph
    7 9
    1 2
    1 3
    2 7
    3 4
    3 5
    4 7
    5 7
    1 6
    6 3
    in this graph, 2 paths are going through node 3, but in my implementation of dfs when we are visiting node 3, only then we would print the second path also
    even though the other path would definitely include some other vertex otherwise, we would not even reach node 3


*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

int bfs(vector<int> adj[], int u, vector<int>& par, vector<vector<int>>& cap, int dst) {

    queue<array<int,2>> q;

    q.push({u, INT_MAX});
    par[u] = -2;

    while(!q.empty()) {
        int u = q.front()[0];
        int cflow = q.front()[1];
        q.pop();

        if(u == dst) {
            return cflow;
        }

        for(int v : adj[u]) {
            if(par[v] == -1 && cap[u][v] > 0) {
                par[v] = u;
                q.push({v, min(cflow, cap[u][v])});
            }
        }
    }

    return 0;
}

// bool dfs(set<int> adj[], int u, vector<vector<int>>& cap, vector<bool>& vis, vector<int>& path, vector<vector<int>>& paths, int dst) {
bool dfs(set<int> adj[], int u, vector<vector<int>>& cap, vector<int>& path, vector<vector<int>>& paths, int dst) {
    path.push_back(u);
    if(u == dst) {
        for(int i=0;i<path.size()-1;i++) {
            adj[path[i]].erase(path[i+1]);
        }
        paths.push_back(path);
        path.pop_back();
        return 1;
    }

    // vis[u] = 1;
    for(int v : adj[u]) {
        // if(!vis[v] && cap[u][v] == 0) {
        //     if(dfs(adj, v, cap, vis, path, paths, dst)) {
        if(cap[u][v] == 0) {
            if(dfs(adj, v, cap, path, paths, dst)) {
                path.pop_back();
                return 1;
            }
        }
    }

    path.pop_back();

    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m, k;
    cin >> n >> m;

    vector<int> adj[n];
    set<int> ogAdj[n];
    vector<vector<int>> cap(n, vector<int>(n));
    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        ogAdj[u].insert(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = 1;
    }

    int ans=0;
    vector<int> par(n, -1);
    while(int cflow = bfs(adj, 0, par, cap, n-1)) {
        ans += cflow;

        int node = n-1;
        while(node != 0) {
            int prev = par[node];

            cap[prev][node] -= cflow;
            cap[node][prev] += cflow;

            // cout << node << " ";
            node = prev;
        }
        // cout << "\n";
        debug(cflow);
        debug(par);

        par = vector<int>(n, -1);
    }
    // for(i=0;i<n;i++) {
    //     for(int j=0;j<n;j++) {
    //         cout << cap[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    vector<vector<int>> paths;
    vector<int> path;
    vector<bool> vis(n);
    // while(dfs(ogAdj, 0, cap, vis, path, paths, n-1));
    while(dfs(ogAdj, 0, cap, path, paths, n-1));

    cout << ans << "\n";
    for(auto& path : paths) {
        cout << path.size() << "\n";
        for(int node : path) {
            cout << node+1 << " ";
        }
        cout << "\n";
    }

    return 0;

}