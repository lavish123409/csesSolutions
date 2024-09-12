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
 
    I appraoch
    we can use something like Central limit theorem which is used for finding probability of getting the sum on a range
    just the twist is that, Central limit theorem is true for when sum is taken for large number of random variables, i.e, >= 30

    PROBLEM
    not able to find any way for discrete case of central limit theorem

    Solution
    it is a basic usage of dp
    when dice is rolled 1 time, we would get sum as
                1   2   3   4   5   6
    with prob   1/6 1/6 1/6 1/6 1/6 1/6
    now, when we would roll the dice next time
    we can take all current sums, and add the outcome of current dice roll
    that is, the sums till current dice roll can be found out by traversing through all sums till last dice roll and adding all possible outcomes of current dice roll
    so, dp[n][i] = probability of sum i when n dice rolls have been made
    and, dp[n][i] = dp[n-1][i-1] * 1/ 6 + dp[n-1][i-2] * 1/ 6 + dp[n-1][i-3] * 1/ 6 + dp[n-1][i-4] * 1/ 6 + dp[n-1][i-5] * 1/ 6 + dp[n-1][i-6] * 1/ 6



*/
 
string ps = "\n";
 
void genSum(int n, int val, int csm, int frq[]) {
 
    if(n == 0) {
        frq[csm]++;
        return;
    }
 
    for(int i=1;i<=val;i++) {
        genSum(n-1, val, csm+i, frq);
    }
 
}
 
void solve() {
    // int i, j, n=2;
    // int sum[6*n+1] = {0};
    
    // genSum(n, 6, 0, sum);
    // double exp = 0;
    // for(i=2;i<=6*n;i++) {
    //     exp += (sum[i] * 1.0 / 36);
    //     cout << i << " : " << sum[i] << "\n";
    // }
    // cout << exp << " : " << exp / 10 << "\n";
    // cout << "\n";
 
    int i, j, n;
    cin >> n;
 
    double dp[n+1][6*n+1];
    memset(dp, 0, sizeof(dp));
 
    for(i=1;i<=6;i++) {
        dp[1][i] = 1.0 / 6;
    }
 
    for(i=2;i<=n;i++) {
        for(j=0; j<=6*i; j++) {
            for(int k=1;k<=6;k++) {
                if(j - k >= 0) {
                    dp[i][j] += dp[i-1][j - k];
                }
            }
            dp[i][j] /= 6;
        }
    }
 
    int a, b;
    cin >> a >> b;
 
    double ans = 0.0;
    for(i=a;i<=b;i++) {
        ans += dp[n][i];
    }
 
    cout << fixed << setprecision(6) << ans << "\n";
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