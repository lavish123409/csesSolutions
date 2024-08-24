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
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
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

    use Ford Fulkerson algorithm to solve the max flow problem
    each edge u-v determines the flow of 1 that robber can go from u to v 
    from the max flow and min-cut theorem, we know that max flow through a graph = min-cut of that graph
    and we want to find the min-cut here, that is the minimum number of edges to remove to separate source and sink, such that there is no flow
    and the bottleneck in each flow would tell which edge to be removed

    Solution
    after finding the maximum flow, just find what vertices are reachable from source
    min-cut would consist of all those edges which have saturated and which are preventing the flow from source to sink
    so, one vertex of min-cut edge would be reachable from source (with positive flow, i.e, flow can still go through them) and other one would not

    find max-flow
    print minimum streets to block
    run the bfs to mark all those vertices which are reachable from source
    traverse all the edge and see if one end point is reachable and other is not, then add it to list of edges

    WA1 - did not know the change required for undirected graph
    we would have to also keep the capacity of edge v->u same as u->v, do not know the reason though

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

int bfs(vector<int> adj[], int u, vector<int>& par, vector<vector<int>>& cap, int dst) {

    queue<array<int,2>> q;
    par[u] = -2;
    q.push({u, 1001});

    while(!q.empty()) {
        int u = q.front()[0];
        int cflow = q.front()[1];
        q.pop();

        if(u == dst) {
            return cflow;
        }

        for(int v : adj[u]) {
            if(par[v] == -1 && cap[u][v] > 0) {
                q.push({v, min(cflow, cap[u][v])});
                par[v] = u;
            }
        }
    }

    return 0;
}

void printAdj(vector<int> adj[], int n, vector<vector<int>>& cap) {
    for(int u=0;u<n;u++) {
        cout << u << " : ";
        for(int v : adj[u]) {
            cout << v << " - " << cap[u][v] << " , ";
        }
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    vector<int> adj[n];
    vector<vector<int>> cap(n, vector<int>(n));
    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;
        // if(u > v) {
        //     swap(u, v);
        // }

        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v]++;
        cap[v][u]++;
    }

    int ans=0;
    vector<int> parent(n, -1);
    while(int cflow = bfs(adj, 0, parent, cap, n-1)) {
        ans += cflow;
        

        int node = n-1;
        while(node != 0) {
            int par = parent[node];

            cap[par][node] -= cflow;
            cap[node][par] += cflow;

            node = par;
        }
        // debug(cflow, ans);
        // printAdj(adj, n, cap);

        parent = vector<int>(n, -1);
    }

    vector<bool> isReachable(n);
    
    queue<int> q;
    q.push(0);
    isReachable[0] = 1;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(int v : adj[u]) {
            if(!isReachable[v] && cap[u][v] > 0) {
                q.push(v);
                isReachable[v] = 1;
            }
        }
    }

    cout << ans << "\n";
    for(int u=0;u<n;u++) {
        for(int v : adj[u]) {
            if(isReachable[u] && !isReachable[v]) {
                cout << u+1 << " " << v+1 << "\n";
            }
        }
    }
    return 0;

}