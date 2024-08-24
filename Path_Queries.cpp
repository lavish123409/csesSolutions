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
 
    peeked the solution, even then also not able to solve the problem
    we just have to think of representing tree paths by the means of array intervals
    thought about one approach
        - enter the node in euler tour before visiting any child
        - then for any node, the root node would be at depth[node] distance left of node in tour
    but the problem was when we would have to update the values, we would have to update it at every position of that node in the tour, which can be O(n)

    the solution is to store the complete sum of paths in euler tour
    and while updating, all descendats value of node to be updated with x, will be updated with x - value[node]

    in fenwick trees, the range update from [l,r] with x would be
        - upd(l, x)
        - upd(r+1, -x)
    

*/
string ps = "\n";

class BIT {
private:
    vector<int> arr;
    vector<ll> bit;
    int n;

public:
    BIT(int n) {
        this->n = n;
        arr.resize(n, 0);
        bit.resize(n+1, 0);
    }

    void upd(int ind, ll val) {
        for(ind++; ind <= n; ind += (ind & -ind)) {
            bit[ind] += val;
        }
    }

    ll qry(int ind) {
        ll ans = 0ll;
        for(ind++; ind; ind -= (ind & -ind)) {
            ans += bit[ind];
        }

        return ans;
    }
};

const int MAXN = int(2e5+5);
// vector<ll> euler;
int tin[MAXN], tout[MAXN];
int timer=0;

void dfs(vector<int> adj[], int u, int par) {
    tin[u] = timer++;

    for(int v : adj[u]) {
        if(v == par) continue;

        dfs(adj, v, u);
    }

    tout[u] = timer++;
}

void solve() {
    
    int n, q, i;
    cin >> n >> q;

    int vals[n];
    for(i=0;i<n;i++) {
        cin >> vals[i];
    }

    vector<int> adj[n];
    BIT bit(2*n);

    for(i=1;i<n;i++) {
        int u, v;
        cin >> u >> v, --u, --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(adj, 0, -1);
    for(i=0;i<n;i++) {
        bit.upd(tin[i], vals[i]);
        bit.upd(tout[i], -vals[i]);
    }

    while(q--) {
        int t;
        cin >> t;

        if(t == 1) {
            int node, val;
            cin >> node >> val, --node;

            bit.upd(tin[node], val - vals[node]);
            bit.upd(tout[node], -(val - vals[node]));
            vals[node] = val;
        }

        else {
            int node;
            cin >> node, --node;

            cout << bit.qry(tin[node]) << "\n";
        }
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