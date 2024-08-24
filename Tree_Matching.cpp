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
    currently, I am thinking that first of all we have to take all degree 1 edges
    and then remove all adjacent vertices of both endpoints
    after that, if vertex have again degree 1, then repeat same process

    put all edges u-v in a queue, if u have degree 1
    take out the edge from queue, and check if edge is still there (edge might have been removed while it was in queue)
    if it is not there, continue with next edge from queue
    otherwise, increment the ans, and remove edge u-v and v-u from adjacency list
    traverse all connected vertices to v and remove the edges
    if any one of those vertices have degree 1 put in the queue
    print the ans

    the above solution's proof is difficult, dp can be tried

    DP solution - kartik arora
    first of all make the tree rooted and think in the terms of parent and children
    for any node we can have 2 choices
        - we would not select any edge from that node to its childen
        - we would select any one edge from it to any one of its children because we cannot select 2 edges having same endpoint
    then, we would start from any random node which is the root of the tree, we would choose node 1
    and we can check for that node what is the maximum matching we can get when we are taking 1 or 0 edge form current node
    for this we can take maximum of both the cases which dp is holding
    for 0 edge, it would be stored in dp[node][0]
    for 1 edge, we can traverse all children and find sum of
        - dp[child][0] for that child as if we are choosing that edge, then that child cannot choose any vertex
        - maximum matching,i.e, max(dp[child][0], dp[child][1]) for other childs
    since, we have to find sum we need to store maximum matching value in prefix and suffix sum

    WA4 - didn't realised that when child==par, then pref[i+1] was not getting initialized
    WA5 - forgot that dp[u][0] would sum of all maximum matchings of children


*/
string ps = "\n";

ll recurse(vector<int> adj[], int u, vector<vector<ll>>& dp, int par) {

    int nc = adj[u].size();
    vector<ll> prf(nc+1), sfx(nc+1);

    dp[u][0] = 0;
    dp[u][1] = 0;
    for(int i=0;i<nc;i++) {
        int child = adj[u][i];
        if(child != par) {
            ll ccmat = recurse(adj, child, dp, u);
            // dp[u][0] = max(dp[u][0], ccmat);
            prf[i+1] = ccmat + prf[i];
        }
        else {
            prf[i+1] = prf[i];
        }
    }

    for(int i=nc-1;i>=0;i--) {
        ll cn = prf[i+1] - prf[i];
        sfx[i] = cn + sfx[i+1];
    }
    debug(prf);
    debug(sfx);

    dp[u][0] = sfx[0];
    for(int i=0;i<nc;i++) {
        if(adj[u][i] != par) {
            dp[u][1] = max(dp[u][1], 1 + prf[i] + dp[adj[u][i]][0] + sfx[i+1]);
        }
        debug(u, i, adj[u][i], prf[i], sfx[i+1], dp[adj[u][i]][0]);
    }

    debug(u+1, dp[u][0], dp[u][1]);
    return max(dp[u][0] , dp[u][1]);
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

    vector<vector<ll>> dp(n, vector<ll>(2, -1));
    cout << recurse(adj, 0, dp, -1) << "\n";

    // for(i=0;i<n;i++) {
    //     cout << dp[i][0] << " : " << dp[i][1] << "\n";
    // }
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