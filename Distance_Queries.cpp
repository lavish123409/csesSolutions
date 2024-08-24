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
    I am thinking that we would try to find the lca for both nodes
    and then add the distance of both nodes from the lca
    also, we would have to add the distance we would use if we would align the nodes at same level

    WA1 (not understood the algorithm and question)
    I was thinking that always the parent index would be less than the child index but it is not true in general case

    WA2 and TLE (bug)
    wrote wrong implementation of going up in the tree
        int ancA = raise(a, i);
    which should be
        int ancA = raise(a, (1 << i));

*/
string ps = "\n";

void dfs(vector<int> adj[], int u, int par, int lgn, vector<vector<int>>& anc, int depth[], int cdepth) {

    depth[u] = cdepth;
    anc[u][0] = par;
    for(int i=1;i<lgn;i++) {
        anc[u][i] = anc[anc[u][i-1]][i-1];
    }
    for(int v : adj[u]) {
        if(v != par) {
            dfs(adj, v, u, lgn, anc, depth, cdepth+1);
        }
    }

}

void solve() {
    
    int i, j, n, q;
    cin >> n >> q;

    int lgn = ceil(log2(n)) + 1;
    vector<vector<int>> anc(n, vector<int>(lgn));
    vector<int> adj[n];
    int depth[n] = {0};
    // int anc[n][lgn];
    anc[0][0] = 0;
    for(i=1;i<n;i++) {
        // int par;
        // cin >> par;
        int u, v;
        cin >> u >> v;
        --u, --v;
        if(u > v) {
            swap(u, v);
        }

        // anc[v][0] = u;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // for(i=1;i<lgn;i++) {
    //     for(int node=0;node<n;node++) {
    //         anc[node][i] = anc[anc[node][i-1]][i-1];
    //     }
    // }

    dfs(adj, 0, 0, lgn, anc, depth, 0);
    auto raise = [&](int node, int dis) {
        for(int i=0;(1 << i) <= dis; i++) {
            if((1 << i) & dis) {
                node = anc[node][i];
            }
        }

        return node;
    };
    debug(anc);
    // for(int i=0;i<n;i++) {
    //     cout << anc[i][0] << " ";
    // }
    // cout << "\n";

    while(q--) {
        int a, b, ans=0;
        cin >> a >> b;

        --a;
        --b;

        if(depth[a] > depth[b]) {
            swap(a, b);
        }

        debug(a, b);
        debug(depth[a], depth[b]);
        ans += (depth[b] - depth[a]);
        b = raise(b, ans);

        // if(a == b) {
        //     cout << 
        // }
        debug(ans);

        for(int i=lgn-1;~i;i--) {
            int ancA = raise(a, (1 << i));
            int ancB = raise(b, (1 << i));
            debug(i, a, b, ancA, ancB);
            if(ancA != ancB) {
                ans += 2 * (1 << i);
                a = ancA;
                b = ancB;
            }
        }

        if(a != b) {
            ans += 2;
        }
        cout << ans << "\n";

    }
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