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
    it can also be solved by modifying approach in previous question
    just earlier, to get the number of paths between u and v, we can do
        number of paths from u to k * number of paths from k to v, for every intermediate vertex k
      / - \   / - \ 
    u - - - k      - v
      \ - /   \ - /

    now for, getting the path with minimum length between u and v, we can do
        minimum length path from u to k + minimum length path from k to v, for every intermediate vertex k
    
    and, while multiplying matrices we can modify exactly that
    currentPathLength = min(currentPathLength, 
                                [a11 a12 a13] * [a11] = a11 + a11 //  minimum path length from 1 to 1 + minimum path length from 1 to 1
                                                [a21] = a12 + a21 // minimum path length from 1 to 2 + minimum path length from 2 to 1
                                                [a31] = a13 + a31 // minimum path length from 1 to 3 + minimum path length from 3 to 1
                            )
    
    so we can find kth power of our adjacency matrix, because multiplying it k times would give path lengths of k
    and print the minimum path length by (A^k)[1][n] between node 1 and node n
    we have to store infinity as 1e18+1, because maximum path length can be 1e18

    WA4
    doing mod while multiplying matrices reduces the infinity
    we should do mod only when, multiplication != infinity

    WA7
    did not realised that mod was not asked in the question
*/
 
string ps = "\n";

const int mod = int(1e9+7);

// vector<vector<ll>> matMul(vector<vector<ll>>& a, vector<vector<ll>>& b, vector<vector<ll>>& mnwtA, vector<vector<ll>>& mnwtB, vector<vector<ll>>& mnwt) {
//     int i, j, k, n=a.size();
//     vector<vector<ll>> ans(n, vector<ll>(n));
//     vector<vector<ll>> mnWt(n, vector<ll>(n));

//     for(i=0;i<n;i++) {
//         for(j=0;j<n;j++) {
//             for(k=0;k<n;k++) {
//                 ans[i][j] += a[i][k] * b[k][j];
//                 ans[i][j] % mod;
//                 mnWt[i][j] = min(mnwtA[i][k], mnwtB[k][j]);
//             }
//         }
//     }
//     mnwt = mnWt;
//     return ans;
// }

// vector<vector<ll>> matExp(vector<vector<ll>>& mat, vector<vector<ll>>& mnwt, int e) {
//     int i, j, n=mat.size();
//     vector<vector<ll>> ans(n, vector<ll>(n));
//     vector<vector<ll>> mnwtAns(n, vector<ll>(n));

//     for(i=0;i<n;i++) {
//         for(j=0;j<n;j++) {
//             ans[i][j] = (i == j);
//         }
//     }

//     while(e) {
//         if(e&1) ans = matMul(ans, mat, mnwt, mnwt, mnwt);
//         mat = matMul(mat, mat, mnwt, mnwt, mnwt);
//         e >>= 1;
//     }

//     return ans;
// }

const ll MAXWT = (ll)(1e18) + 1;
vector<vector<ll>> matMul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
// void matMul(vector<vector<ll>>& ans, vector<vector<ll>>& a, vector<vector<ll>>& b) {
    int i, j, k, n=a.size();
    vector<vector<ll>> ans(n, vector<ll>(n, MAXWT));

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            for(k=0;k<n;k++) {
                ans[i][j] = min(ans[i][j], a[i][k] + b[k][j]);
                // if(ans[i][j] != MAXWT) {
                //     ans[i][j] %= mod;
                // }
            }
        }
    }
    return ans;
}

vector<vector<ll>> matExp(vector<vector<ll>>& mat, int e) {
    int i, j, n=mat.size();
    vector<vector<ll>> ans(n, vector<ll>(n, MAXWT));

    for(i=0;i<n;i++) {
        ans[i][i] = 0;
    }

    // for(i=0;i<n;i++) {
    //     for(j=0;j<n;j++) {
    //         ans[i][j] = (i == j);
    //     }
    // }

    while(e) {
        if(e&1) ans = matMul(ans, mat);
        // if(e&1) matMul(ans, ans, mat);
        // if(e&1) {
        //     vector<vector<ll>> cans = matMul(ans, mat);
        //     for(i=0;i<n;i++) {
        //         for(j=0;j<n;j++) {
        //             ans[i][j] = min(cans[i][j], ans[i][j]);
        //         }
        //     }
        // }
        // if(e&1) {
        //     for(i=0;i<n;i++) {
        //         for(j=0;j<n;j++) {
        //             ans[i][j] = mat[i][j];
        //         }
        //     }
        // }
        mat = matMul(mat, mat);
        // matMul(mat, mat, mat);
        e >>= 1;
    }

    return ans;
}

void solve() {

    int i, n, m, k;
    cin >> n >> m >> k;
    
    vector<vector<ll>> adj(n, vector<ll>(n, MAXWT));
    // vector<vector<ll>> mnwt(n, vector<ll>(n, MAXWT));

    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        // adj[u][v]++;
        // int w;
        // cin >> w;
        // mnwt[u][v] = min(mnwt[u][v], 1ll * w);
        
        // adj[u][v]++;
        int w;
        cin >> w;
        adj[u][v] = min(adj[u][v], 1ll * w);
    }

    // debug(mnwt);

    // adj = matExp(adj, mnwt, k);
    debug(adj);
    adj = matExp(adj, k);
    // cout << adj[0][1] << "\n";
    debug(adj);
    // debug(mnwt);
    if(adj[0][n-1] == MAXWT) {
        cout << "-1\n";
        return;
    }
    // cout << adj[0][n-1] % mod << "\n";
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