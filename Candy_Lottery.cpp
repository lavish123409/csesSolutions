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
    this question to similar to the one that, we have to find the expected value of highest value we would get on rolling the die n times
    here, instead of having 6 outcomes on every dice roll, we have k candies to give to nth child
    if we would see the formula of EV
        EV = 1 * probability that maximum is 1 + 2 * probability that maximum is 2 + ... + k * probability that maximum is k
    now, how would we calculate the probability that we got this maximum?
    we would get it by simulating the giving of candy
    in first candy, we would have probability of every candy to be 1/k
    now for second child we can make a table
      1 2 3 ... k
    1 1 2 3 ... k
    2 2 2 3 ... k
    3 3 3 3 ... k
        ...
        ...
    k k k k ... k
    where row is depicting the number of candies that first child got,
    and column is depicting the number of candies that second child got and the maximum is result in that cell
    we would represent dp[n][i] as the probability that i is the maximum candies that any child has gotten till nth child
    we can simulate for every child the number of candies which it would get, by passing the probabilities of current maximum to the max(current_maximum, current_candies)
    and finally find the expected value according to the formula, as now we have the probabilities

    for child from 1 to n:
        for maximum_candies_till_now from 1 to k:
            for current_candies from 1 to k:
                dp[child][max(maximum_candies_till_now, current_candies)] += dp[previous_child][maximum_candies_till_now] * 1 / k

    EV = 0
    for maximum_candies_value from 1 to k:
        EV += (maximum_candies_value * dp[n][maximum_candies_value])

    MISTAKE
    did not realize that expected value would be different for each cell
    also, k turns means that we have to run the loop k times, that is we have to take the dp array of size dp[k+1][64]

    Solution
    though the solution is much easier
    if we would see the 2d table made above, we can see that any i number of candies is maximum in the range i^2 - (i-1)^2, the area of k square - area of k-1 square
    so we can also find the expected value by
        EV = 1 * 1 + 2 * 3 + 3 * 5 + ... k * (k^2 - (k-1)^2)
    similarly, we can do it for 3 children, which would become the cuboid, that is maximum in the range i^3 - (i-1)^3, the volume of k square - volume of k-1 square
    so, for n children
        EV = 1 * (1^n - 0^n) + 2 * (2^n - 1^n) + 3 * (3^n - 2^n) + ... k * (k^n - (k-1)^n)
    
*/
// #define double long double

string ps = "\n";

void solve() {
    int i, j, n, k;
    cin >> n >> k;

    double dp[n+1][k+1] = {0.0};
    for(i=1;i<=k;i++) {
        dp[1][i] = 1.0 / k;
    }

    for(i=1;i<n;i++) {
        for(j=1;j<=k;j++) {
            for(int candies=1; candies <= k; candies++) {
                dp[i+1][max(j, candies)] += dp[i][j] / k;
            }
        }
    }

    // for(i=0;i<=n;i++) {
    //     for(j=0;j<=k;j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    double ans = 0.0;
    for(i=1;i<=k;i++) {
        ans += i * dp[n][i];
        debug(i, dp[n][i]);
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