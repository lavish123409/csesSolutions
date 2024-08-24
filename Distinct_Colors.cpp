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
    we can combine euler tour and finding distinct numbers in the range techniques
    
    for euler tour, we can store in and out time for every vertex

    for finding distinct numbers in the range, we cna use mo's algorithm
    that is, store the queries in increasing order of r_i
    at every index add the distinct number to fenwick tree if it was not there
    and if it was there, remove it from the previous index, and add it to current index
    and take sum from l_i to r_i using fenwick tree

    WA1
    wrote wrong bound for update in bit tree
        for(ind++; ind < MAXN; ind += (ind & -ind))
    which should be
        for(ind++; ind < 2*MAXN; ind += (ind & -ind))

*/
string ps = "\n";

const int MAXN = int(2e5+5);
int tin[MAXN], tout[MAXN], bit[2*MAXN];
int colors[MAXN];
int timer = 0;

void upd(int ind, int val) {
    for(ind++; ind < 2*MAXN; ind += (ind & -ind)) {
        bit[ind] += val;
    }
}

int qry(int ind) {
    int ans = 0;
    for(ind++; ind; ind -= (ind & -ind)) {
        ans += bit[ind];
    }

    return ans;
}

void dfs(vector<int> adj[], int u, int par) {

    tin[u] = timer++;

    for(int v : adj[u]) {
        if(v == par) continue;

        dfs(adj, v, u);
    }

    tout[u] = timer++;
}

void solve() {
    int i, n;
    cin >> n;

    for(i=0;i<n;i++) {
        cin >> colors[i];
    }

    vector<int> adj[n];
    for(i=1;i<n;i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(adj, 0, -1);

    int ans[n];
    array<int,2> toutv[n];
    for(i=0;i<n;i++) {
        toutv[i] = {tout[i], i};
    }

    sort(toutv, toutv + n);

    map<int,int> lcp;
    for(i=0;i<n;i++) {
        int u = toutv[i][1];
        int l = tin[u];
        int r = tout[u];
        debug(i, u, l, r);

        if(lcp.count(colors[u])) {
            upd(lcp[colors[u]], -1);
        }
        upd(r, 1);
        lcp[colors[u]] = r;

        ans[u] = qry(r) - qry(l-1);
    }

    for(i=0;i<n;i++) {
        cout << ans[i] << " ";
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