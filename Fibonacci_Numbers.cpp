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

// tip: its a good alternative to check the not version of given problem, and think about it to solve
// for ex, Christmas party
 
/*
 
    I appraoch
    we know that fibonacci number is given by this relation
        f(n) = f(n-1) + f(n-2), where f(0) = 0 and f(1) = 1
    we can use dp to store all fibonacci numbers till n and print the nth number by dp[n]
    or, we can only take last 2 numbers a and b and find fibonacci for current number c
    then, in next iteration, put a=b and b=c and then find fibonacci for current number c till n

    it would not be possible because constraints are 10^18
    since, constraints are so high we would have to use log(n) complexity

    we know that for any recurrence relation question, we can use matrix exponentiation technique
    if the recurrence is f(n) = f(n-1) + f(n-2)
    then, we can write it in matrix form like this
        [0 1][f(n-2)] = [       f(n-1)         ]
        [1 1][f(n-1)]   [f(n) = f(n-1) + f(n-2)]

    we know, f(0)=0, f(1)=1, then for f(3)
        [f(2)] = F * F * [0], where F = [0 1]      
        [f(3)]           [1]            [1 1]
    when, we multiply [0] with F^1, we get [f(1)], so looking at the denominator we have raise F to the power of (n-2)
                      [1]                  [f(2)]

    so, for f(n) we have to find F^(n-1) and then, multiply it with [0]
                                                                    [1]

    we can use binary exponentiation for power
    
*/
string ps = "\n";

const int mod = int(1e9+7);

vector<vector<ll>> matMul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
    return {
        {a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]},
        {a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]}
    };
}

vector<vector<ll>> matExp(vector<vector<ll>>& mat, ll e) {
    vector<vector<ll>> ans = {{1, 0}, {0, 1}};
    while(e) {
        if(e&1) {
            ans = matMul(ans, mat);
            ans[0][0] %= mod;
            ans[1][0] %= mod;
            ans[0][1] %= mod;
            ans[1][1] %= mod;
        }
        mat = matMul(mat, mat);
        mat[0][0] %= mod;
        mat[1][0] %= mod;
        mat[0][1] %= mod;
        mat[1][1] %= mod;
        e >>= 1;
    }
    return ans;
}

void solve() {
    ll n;
    cin >> n;

    if(n == 0) {
        cout << "0\n";
        return;
    }

    vector<vector<ll>> inm = {{0, 1}, {1, 1}};
    cout << matExp(inm, n-1)[1][1] % mod << "\n";
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