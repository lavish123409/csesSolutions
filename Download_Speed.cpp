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
    the connection which specifies how fast a computer can send data to another computer, is the maximum capacity of that edge
    we have to find what is the maximum flow through the graph, giving maximum download speed

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

class Edge {
public:
    int u, v;
    ll flow;
    ll capacity;
    bool isResidual;
    Edge* residual;

    Edge(int u, int v, int capacity, bool isResidual) {
        this->u = u;
        this->v = v;
        this->flow = 0ll;
        this->capacity = capacity;
        this->isResidual = isResidual;
    }

    ll getRemainingCapacity() {
        return capacity - flow;
    }

    void updateFlow(ll flow) {
        this->flow += flow;
    }

    void setResidual(Edge* residual) {
        this->residual = residual;
    }

    Edge* getResidual() {
        return residual;
    }
};

vector<pair<int,ll>> path;
int dfs(vector<Edge*> adj[], int u, vector<int>& vis, int visTkn, int dst, ll cflow) {
    if(u == dst) {
        // debug("======================================================================================");
        return cflow;
    }

    // if(vis[u] == visTkn) {
    //     return 0;
    // }

    vis[u] = visTkn;
    // debug(u, visTkn, dst);
    for(Edge* edge : adj[u]) {
        if(edge->getRemainingCapacity() > 0 && vis[edge->v] != visTkn) {
            // path.push_back({edge->v, edge->getRemainingCapacity()});
            int bottleneck = dfs(adj, edge->v, vis, visTkn, dst, min(cflow, edge->getRemainingCapacity()));
            // debug(u, edge->v, path, bottleneck);
            // path.pop_back();
            if(bottleneck != 0) {
                edge->updateFlow(bottleneck);
                edge->getResidual()->updateFlow(-bottleneck);
                return bottleneck;
            }
        }

    }
    // vis[u] = -1;

    return 0;
}

ll bfs(vector<int> adj[], int u, vector<int>& parent, vector<vector<ll>>& capacity, int dst) {

    int n = parent.size();
    // vector<bool> vis(n);
    queue<pair<int,ll>> q;

    q.push({u, LONG_LONG_MAX});
    parent[u] = -2;
    // vis[u] = 1;
    while(!q.empty()) {
        int u = q.front().first;
        ll cflow = q.front().second;
        q.pop();
        debug(u, cflow);

        if(u == dst) {
            debug("r", cflow);
            return cflow;
        }

        for(int v : adj[u]) {
            debug(u,v,capacity[u][v]);
            if(parent[v] == -1 && capacity[u][v]) {
                q.push({v, min(cflow, capacity[u][v])});
                // vis[v] = 1;
                parent[v] = u;
            }
        }
    }

    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    // vector<Edge*> adj[n];
    // // vecotr<int> ad[n];
    // for(i=0;i<m;i++) {
    //     int u, v, c;
    //     cin >> u >> v >> c;
    //     u--;
    //     v--;

    //     Edge* cedge = new Edge(u, v, c, 0);
    //     Edge* redge = new Edge(v, u, 0, 1);
    //     cedge->setResidual(redge);
    //     redge->setResidual(cedge);

    //     adj[u].push_back(cedge);
    //     adj[v].push_back(redge);
    //     // ad[u].push_back(v);
    // }

    // ll ans = 0ll;
    // int cflow = 0, visTkn=0;
    // int ind=0;
    // vector<int> vis(n, -1);
    // path.push_back({0, 0});
    // do {
    //     cflow = dfs(adj, 0, vis, visTkn, n-1, LONG_LONG_MAX);
    //     visTkn++;
    //     ans += cflow;
    //     debug(cflow, visTkn, ans);
    //     // if(ind++ > 100) break;
    // } while(cflow != 0);

    // // dfs1(ad, 0, )

    // cout << ans << "\n";

    vector<int> adj[n];
    vector<vector<ll>> capacity(n, vector<ll>(n));
    for(i=0;i<m;i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += c;
    }

    vector<int> parent(n, -1);
    ll ans = 0ll;
    while(ll cflow = bfs(adj, 0, parent, capacity, n-1)) {
        ans += cflow;

        int node = n-1;
        while(parent[node] >= 0) {
            int u = parent[node];
            int v = node;

            debug(u, v, capacity[u][v], capacity[v][u]);
            capacity[u][v] -= cflow;
            capacity[v][u] += cflow;
            debug(u, v, capacity[u][v], capacity[v][u]);
            node = u;
        }
        debug(cflow, parent);

        parent = vector<int>(n, -1);
    }

    cout << ans << "\n";
    return 0;

}