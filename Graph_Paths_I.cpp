#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
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
 
// tip: try to think about recursive solutions for Mathematical problems
// sometimes it becomes too complex to use just 1 formula to calculate complete answer
// for ex, Josephus Problem
 
// tip: its a good alternative to check the not version of given problem, and think about it to solve first
// for ex, Christmas party
 
/*
 
    I approach
    I was thinking that we can store the cycle length of the cycle in which the current node belongs for every node
    then, for every node we can find for every node
        dis(source, node) + q * cycle_length + dis(node, destination) = k
        => k - (dis(source, node) + dis(node, destination)) % cycle_length == 0
        then, number_of_paths += k - (dis(source, node) + dis(node, destination)) / cycle_length
    
    PROBLEM
    not able to code to get cycle length for every node
    [once have to try searching for its code]

    Solution
    if store all the edges, in a adjacency matrix A
    then, number of paths having 1 edge between u and v is given by A[u][v]
    and, number of paths having 2 edges between u and v is given by (A^2)[u][v]
    and, number of paths having 3 edges between u and v is given by (A^3)[u][v]
    and so on

    to get the number of paths between u and v, we can do
        number of paths from u to k * number of paths from k to v, for every intermediate vertex k
      / - \   / - \ 
    u - - - k      - v
      \ - /   \ - /
    for ex, in this case, number of paths from u to v = number of paths from u to k * number of paths from k to v = 3 * 2 = 6

    and, in multiplying matrices we are doing exactly that
    [a11 a12 a13] * [a11] = a11 * a11 // paths from 1 to 1 wih intermediate vertex 1
                    [a21] = a12 * a21 // paths from 1 to 1 wih intermediate vertex 2
                    [a31] = a13 * a31 // paths from 1 to 1 wih intermediate vertex 3
    
    so we can find kth power of our adjacency matrix
    and print the number of paths by (A^k)[1][n] between node 1 and node n
    
*/
 
string ps = "\n";
 
const int mod = int(1e9+7);
 
vector<vector<ll>> matMul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
    int i, j, k, n=a.size();
    vector<vector<ll>> ans(n, vector<ll>(n));
 
 
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            for(k=0;k<n;k++) {
                ans[i][j] += a[i][k] * b[k][j];
                ans[i][j] %= mod;
            }
        }
    }
 
    return ans;
}
 
vector<vector<ll>> matExp(vector<vector<ll>>& mat, int e) {
    int i, j, k, n = mat.size();
    vector<vector<ll>> ans(n, vector<ll>(n));
    
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            ans[i][j] = (i == j);
        }
    }
    
    while(e) {
        if(e&1) ans = matMul(ans, mat);
        mat = matMul(mat, mat);
        e >>= 1;
    }
 
    return ans;
}
 
void solve() {
 
    int i, n, m, k;
    cin >> n >> m >> k;
 
    vector<vector<ll>> adj(n, vector<ll>(n));
    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
 
        adj[u][v]++;
    }
 
    adj = matExp(adj, k);
    cout << adj[0][n-1] << "\n";
 
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