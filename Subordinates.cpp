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
    although it is a tree problem, I am not able to think about any tree approach
    we would take a adjacency list and push the current index to its boss's adjacency list
    at last we can count the size of every list, which would be the solution
    
    or maybe, we can use a frequency array and increment the count of boss for current index

    PROBLEM
    this would give us the number of children, but we want to get size of subtree

    treat it as a graph, from every node go to its children
    and calculate their subordinates, and store it in the answer
    and return 1 + number of subordinates (because for its parent it would also be counted as a subordinate along with its children)



*/
string ps = "\n";

int dfs(vector<int> adj[], int u, vector<int>& ans) {
    int ns=0;
    for(int v : adj[u]) {
        ns += dfs(adj, v, ans);
    }

    ans[u] = ns;
    return 1 + ns;
}

void solve() {
    int i, n;
    cin >> n;

    vector<int> adj[n];
    for(i=0;i<n-1;i++) {
        int x;
        cin >> x;

        adj[x-1].push_back(i+1);
    }

    vector<int> ans(n);
    dfs(adj, 0, ans);

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