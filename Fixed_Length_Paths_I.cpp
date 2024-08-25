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
 
    Solution
    for any one node, we can find the number of k length paths passing through it
    we can go through all its descendants and count the number of nodes which are at depth d, using cnt[d]
    we would be doing it by traversing through all of its children
    suppose, we are visiting all descendants of ith child and we are on node with depth d
    now, we can make a k-length path from the node which have depth k - d and which have occurred in any of the previous child, that is, till i-1
    and we have already counted its number in cnt[k - d], so we can add it to the answer
    we would calculate this for all the nodes above and below depth d for ith child

    the challenge is to do it for every node because
        - the k-length path can go through the root, or
        - any one of its children
        - recursively, for every node

    we can use centroid at every level, because taking centroid can guarantee that their would be at most logn level next
    this is because, we are roughly reducing the number of nodes by half at every level

    TLE1
    was setting complete cnt to 0
    although, we can only set till max depth which we are going while finding k-length paths

    WA1
    ans can go upto long long, as in star graph the total number of 2 length paths can be O(n^2)

*/
string ps = "\n";

const int MAXN = int(2e5 + 5);
int sbt[MAXN];
bool isRemoved[MAXN];

int dfs(vector<int> adj[], int u, int par) {

    sbt[u] = 1;
    for(int v : adj[u]) {
        if(v == par || isRemoved[v]) continue;

        sbt[u] += dfs(adj, v, u);
    }

    return sbt[u];
}

int findCentroid(vector<int> adj[], int u, int par, int tn) {
    for(int v : adj[u]) {
        if(v == par || isRemoved[v]) continue;

        if(sbt[v] * 2 > tn) return findCentroid(adj, v, u, tn);
    }

    return u;
}

int cnt[MAXN];
ll ans = 0ll;
int K;
int mxd = 0;

void findAns(vector<int> adj[], int u, int par, int d, bool contri) {
    if(d > K) return;
    mxd = max(mxd, d);

    if(contri) {
        ans += cnt[K - d];
    }
    else {
        cnt[d]++;
    }

    for(int v : adj[u]) {
        if(v == par || isRemoved[v]) continue;

        findAns(adj, v, u, d+1, contri);
    }
}


void findAns(vector<int> adj[], int u, int par) {
    // memset(cnt, 0, sizeof(cnt));
    mxd = 0;
    cnt[0] = 1;

    int tn = dfs(adj, u, par);
    int centroid = findCentroid(adj, u, par, tn);
    for(int v : adj[centroid]) {
        if(v == par || isRemoved[v]) continue;

        findAns(adj, v, centroid, 1, 1);
        findAns(adj, v, centroid, 1, 0);
    }

    for(int i=0;i<=mxd; i++) {
        cnt[i] = 0;
    }
    // vector<int> nset = adj[centroid];
    // for(int v : adj[centroid]) {
    //     adj[v].erase(centroid);
    // }
    // adj[centroid].clear();
    isRemoved[centroid] = 1;

    // cout << u << " : " << centroid << " = " << ans << "\n";
    for(int v : adj[centroid]) {
        if(!isRemoved[v]) {
            findAns(adj, v, centroid);
        }
    }

}

void solve() {
    // memset(isRemoved, 0, sizeof(isRemoved));

    int i, n, k;
    cin >> n >> k;
    K = k;

    vector<int> adj[n];
    for(i=1;i<n;i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        // adj[u].insert(v);
        // adj[v].insert(u);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    findAns(adj, 0, -1);
    cout << ans << "\n";

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