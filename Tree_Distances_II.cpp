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
    we would use dp approach to solve this problem
    first of all we would root the tree and then calculate the sum of paths from root to its all children
    we can find the answer for every children of current node
    and then the edge from current node to its child would be used everytime when we would travel to one of the nodes from that child's subtree
    so, in total one child would contribute the sum of paths to every one of its descendants and the number of descendants because of using the edge from parent
    so, for root
        ans[root] = solve(child) + numberOfNodes(child's subtree)
    then, we have to cover the case in which we can travel from child to parent also
    so, after the answer to parent has been calculated we would do another traversal to add parent's contribution to child
    so, for every child
        ans[child] += (ans[parent] - child's contribution) + numberOfNodes(parent's subtree - child subtree)
    we can store the contribution of every child for a parent in a 2d array and total number of nodes under a node in a 1d array

    WA1 - same old overflow
    the contribution of any node can overflow, so it should be ll


*/
string ps = "\n";

const int MAXN = int(2e5+5);
// vector<vector<array<int,2>>> cont(MAXN, vector<array<int,2>>(MAXN));
map<int, map<int, array<ll,2>>> cont;
// array<int,2> cont[MAXN][MAXN];
int totalNodes[MAXN];

array<ll,2> dfs1(vector<int> adj[], int u, int par, vector<ll>& ans) {
    debug(u);

    int nodes=1;
    ll uans=0;
    for(int& v : adj[u]) {
        if(v != par) {
            array<ll,2> cans = dfs1(adj, v, u, ans);
            cont[u][v][1] = cans[1];
            cont[u][v][0] = (cans[0] + cans[1]);
            nodes += cans[1];
            uans += cont[u][v][0];
        }
    }

    ans[u] = uans;
    totalNodes[u] = nodes;
    return {uans, nodes};
}

void dfs2(vector<int> adj[], int u, ll smta, int tn, int par, vector<ll>& ans) {

    ans[u] += (smta + tn);
    for(int& v : adj[u]) {
        if(v != par) {
            dfs2(adj, v, ans[u] - cont[u][v][0], tn + (totalNodes[u] - totalNodes[v]), u, ans);
        }
    }
}

void solve() {
    int i, n;
    cin >> n;
    debug(n);

    vector<int> adj[n];
    for(i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> ans(n);
    dfs1(adj, 0, -1, ans);
    // for(i=0;i<n;i++) {
    //     cout << ans[i] << " ";
    // }
    // cout << "\n";

    dfs2(adj, 0, 0, 0, -1, ans);
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