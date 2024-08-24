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

    it is a standard problem of Maximum bipartite matching
    connect all boys vertices to all girls vertices with capacity 1
    make a source node and connect it to all boys vertices with capacity 1
    make a sink node and connect it to all girls vertices with capacity 1
    find max flow using edmond-karp algo
    then using min-cut theorem (or edges with 0 residual flow), find edges of possible matchings

    WA1 - nodes of boys and girls can have multiple edges between them
    // tip : if you feel something is going wrong, then try that solution
    // if that solution changes the answer, revert back after trying, otherwise keep it as it is
    // for ex: I thought of multiple edges here, but denied it by saying that question would not give potential pairs 2 times, but it gave

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

int bfs(vector<int> adj[], int u, vector<int>& par, vector<vector<int>>& cap, int dst) {

    queue<array<int,2>> q;
    par[u] = -2;
    q.push({u, INT_MAX});

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

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m, k;
    cin >> n >> m >> k;

    int tn = n + m + 2;
    vector<int> adj[tn];
    vector<vector<int>> cap(tn, vector<int>(tn));

    for(i=0;i<k;i++) {
        int u, v;
        cin >> u >> v;
        v += n;

        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = 1;
    }

    for(i=0;i<n;i++) {
        adj[0].push_back(i+1);
        adj[i+1].push_back(0);
        cap[0][i+1]++;
    }
    
    for(i=0;i<m;i++) {
        adj[i+1+n].push_back(tn-1);
        adj[tn-1].push_back(i+1+n);
        cap[i+1+n][tn-1]++;
    }

    debuga(adj, 0, tn-1);

    vector<int> par(tn, -1);
    int ans=0;
    while(int cflow = bfs(adj, 0, par, cap, tn-1)) {
        ans += cflow;

        int node = tn-1;
        while(node != 0) {
            int prev = par[node];

            cap[prev][node] -= cflow;
            cap[node][prev] += cflow;

            node = prev;
        }
        debug(cflow);
        debug(par);

        par = vector<int>(tn, -1);
    }
    debug(cap);
    // for(i=1;i<=n;i++) {
    //     for(int j=1;j<=m;j++) {
    //         cout << cap[i][j+n] << " ";
    //     }
    //     cout << "\n";
    // }

    set<array<int,2>> flowEdges;
    for(int u=1;u<=n;u++) {
        for(int v : adj[u]) {
            if(v != 0 && cap[u][v] == 0) {
                flowEdges.insert({u, v - n});
            }
        }
    }


    cout << ans << "\n";
    for(auto& edge : flowEdges) {
        cout << edge[0] << " " << edge[1] << "\n";
    }
    return 0;

}