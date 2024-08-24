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
 
    peeked the solution
    we can flatten the tree based on euler tour and use segment tree or fenwick tree to answer queries
    usually, in euler tour we would insert the node in tour, whenever we would visit it
    but in this case we would insert the node whenever we are entering it, and second time when we are leaving
    in this way, we can be sure that in the tour, any node is present at most 2 times at tin(entering time) and tout(leaving time)
    and in order to calculate the sum of subtree, we would have to calculate sum(tin(node), tout(node)) / 2, because every node's value would have came 2 times
    and for update, we would have to update at tin and tout

    other solution
    we can skip storing value at tin[node], then we can find subtree sum by sum(tin(node), tout(node)), without division
    and then we can skip storing euler array

*/
string ps = "\n";

// class BIT {
// private:
//     int n;
//     vector<ll> arr, bit;

// public:
//     BIT(vector<ll>& arr) {
//         this->arr = arr;
//         n = arr.size();
//         bit = vector<ll>(n+1);
//         build();
//     }

//     void build() {
//         int i;
//         for(i=0;i<n;i++) {
//             upd(i, arr[i]);
//         }
//     }

//     void upd(int ind, int x) {
//         for(ind++; ind <= n; ind += (ind & -ind)) {
//             bit[ind] += x;
//         }
//     }

//     ll queryUtil(int ind) {
//         ll ans = 0ll;
//         for(ind++; ind > 0; ind -= (ind & -ind)) {
//             ans += bit[ind];
//         }

//         return ans;
//     }

//     ll query(int a, int b) {
//         return queryUtil(b) - queryUtil(a-1);
//     }


// };

const int MAXN = int(2e5+5);
// vector<ll> euler;
int tin[MAXN], tout[MAXN];
int timer=0;

ll vals[MAXN], bit[2*MAXN];

void upd(int ind, int dff) {
    for(ind++; ind < 2*MAXN; ind += (ind & -ind)) {
        bit[ind] += dff;
    }
}

ll query(int ind) {
    ll ans = 0ll;
    for(ind++; ind > 0; ind -= (ind & -ind)) {
        ans += bit[ind];
    }

    return ans;
}

void dfs(vector<int> adj[], int u, int par) {

    // tin[u] = euler.size();
    tin[u] = timer++;
    // euler.push_back(vals[u]);

    for(int v : adj[u]) {
        if(v == par) continue;

        dfs(adj, v, u);
    }

    tout[u] = timer++;
    // euler.push_back(vals[u]);
}

void solve() {
    
    int i, n, q;
    cin >> n >> q;

    // int vals[n];
    vector<int> adj[n];
    for(i=0;i<n;i++) {
        cin >> vals[i];
    }
    debuga(vals, 0, n-1);

    for(i=1;i<n;i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(adj, 0, -1);
    for(i=0;i<n;i++) {
        upd(tout[i], vals[i]);
    }
    // debug(euler);
    debuga(tin, 0, 2*n-2);
    debuga(tout, 0, 2*n-2);

    // BIT bit(euler);

    while(q--) {
        int t;
        cin >> t;
        debug(t);

        if(!(t-1)) {
            int node, val;
            cin >> node >> val;
            node--;
            debug(node, val);

            // int dff = val - bit.query(tin[node], tin[node]);
            // bit.upd(tin[node], dff);
            // bit.upd(tout[node], dff);
            upd(tout[node], -vals[node]);
            vals[node] = val;
            upd(tout[node], +vals[node]);
        }
        else {
            int node;
            cin >> node;
            node--;
            debug(node);

            // cout << bit.query(tin[node], tout[node]) / 2<< "\n";
            cout << query(tout[node]) - query(tin[node]) << "\n"; // because at tin[node] value would be 0, so no need to do query(tout[node]) - query(tin[node] - 1)
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