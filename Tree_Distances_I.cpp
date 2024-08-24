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
    currently, I am thinking that for any node, the node which is farthest from it would be in some direction
    suppose, there are 2 nodes in the tree which forms the tree's diameter,i.e, u-v
    then, for any node the most distant node would be either in the direction from u->v or from v->u
    for ex, if some node is nearer to u, then most distant node would be v or some other node in the direction of v
    simmilarly, for any node nearer to v

    we can take any random node, do 1st dfs to find one end of tree's diameter
    then, do 2nd dfs to find the maximum distant node from it, and along with it find the maximum distance for any node away from it
    for ex, consider this tree
    1-2-3-4-5
    distance from 1 - 0, 1, 2, 3, 4
    then do, the 3rd dfs from the node furthest form 1 ,i.e, 5 in this case and along with it find the maximum distance for any node away from it
    1-2-3-4-5
    distance from 5 - 4, 3, 2, 1, 0
    and, then take the maximum of both the distances



*/
string ps = "\n";

array<int,2> dfs(vector<int> adj[], int u, vector<int>& dp, int par, int disSrc) {
    int fn=u;
    int dis=0;

    for(int v : adj[u]) {
        if(v != par) {
            array<int,2> cans = dfs(adj, v, dp, u, disSrc+1);
            if(cans[0] >= dis) {
                dis = cans[0];
                fn = cans[1];
            }
        }
    }
    dp[u] = max(dp[u], disSrc);

    return {dis+1, fn};
}

void solve() {
    int i, n;
    cin >> n;

    vector<int> adj[n];
    for(i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(n, -1);
    array<int,2> cans = dfs(adj, 0, dp, -1, 0);
    debug(cans);
    cans = dfs(adj, cans[1], dp, -1, 0);
    debug(cans);
    cans = dfs(adj, cans[1], dp, -1, 0);
    debug(cans);

    for(i=0;i<n;i++) {
        cout << dp[i] << " ";
    }
    cout << "\n";

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