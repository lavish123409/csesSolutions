#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
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
template<typename T>
void printma(T a[], T b[], int l, int r, function<ll(ll,ll)> merge) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(merge(a[i],b[i])); cerr << "}]\n";}
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#define debugma(x, y, l, r, merge) cerr << "[" << #x << "," << #y << "] = ["; printma(x, y, l, r, merge)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#endif
 
 
 
/*
 
    I approach
    we can store the subtree size of every node
    and then traverse every node and check whether it can be centroid or not
        - if its all children have <= n/2 nodes
        - if total_nodes - subtree_size[node] <= n/2 nodes, this would be its parent node which would become its child
    if it is store it in the answer

    Solution
    we do not need to calculate the number of nodes for the parent of node, it would be always less than n/2 [need to verify it from somewhere]
    according to Gaurav Sen in {What is Centroid Decomposition? - YT}, the idea is to start from root, and see if its all children are <= n/2
    if not, then move towards heaviest node, because tree would become more balanced while moving towards heaviest nodes

*/
string ps = "\n";

const int MAXN = int(2e5+5);
int sbt[MAXN];

void dfs(vector<int> adj[], int u, int par) {
    sbt[u] = 1;
    for(int v : adj[u]) {
        if(v == par) continue;

        dfs(adj, v, u);
        sbt[u] += sbt[v];
    }
}

// void findCentroid(vector<int> adj[], int u, int par, int& ans) {
//     int totalNodes = sbt[0];
//     bool cbc = 1;
//     for(int v : adj[u]) {
//         if(v == par) continue;

//         if(sbt[v] > totalNodes / 2) {
//             cbc = 0;
//             break;
//         }
//     }

//     if(totalNodes - sbt[u] > totalNodes / 2) {
//         cbc = 0;
//     }

//     if(cbc) {
//         ans = u;
//         return;
//     }

//     for(int v : adj[u]) {
//         if(v == par) continue;

//         findCentroid(adj, v, u, ans);
//     }
// }

int findCentroid(vector<int> adj[], int u, int par) {
    int totalNodes = sbt[0];
    for(int v : adj[u]) {
        if(v == par) continue;

        if(sbt[v] * 2 > totalNodes) return findCentroid(adj, v, u);
    }

    return u;
}

void solve() {

    int n, i;
    cin >> n;

    vector<int> adj[n];
    for(i=1;i<n;i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(adj, 0, -1);
    debuga(sbt, 0, n-1);

    int ans = 0;
    // findCentroid(adj, 0, -1, ans);
    // cout << ans+1 << "\n";
    cout << findCentroid(adj, 0, -1) + 1 << "\n";

}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    // int t;
    // cin >> t;
 
    // while(t--)
    // {
        solve();
    // }
 
    return 0;
}