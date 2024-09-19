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
    if we can find some way by which we can get the probability of new inversions when we would add nth number
    then, we can do dp to find the probability for finding inversions for n numbers

    Solution
    instead of finding out probability by dp, we can directly find the EV by finding the number of inversions for every pair of ai and aj
    for every pair of ai and aj, total number of possible pairs we can make is ai * aj
    then, probability of choosing one pair from all those pairs would be 1 / (ai * aj)
    and, total number of inversions in them would be (i < j)
        - if ai < aj, then number of inversions would be \binom{ai}{2}, because we can choose the values for 2 places from ai values
            (ai,1), (ai-1,1), ... (2,1), (ai,2), (ai-1,2)....
        - if ai > aj, then number of inversions would be \binom{aj}{2} + ((ai - aj) * aj), because we can choose the values for 2 places from ai values

    in total we would have to add (number of inversions) / (total pairs), for all pairs to the answer

    WA
    due to some newly added test cases, it is giving WA for normal integer arithmetics because long double is not enough for the precision
    
*/
// #define double long double

string ps = "\n";

void solve() {
    
    int i, n;
    cin >> n;

    int r[n];
    for(i=0;i<n;i++) {
        cin >> r[i];
    }

    double ans = 0.0;
    for(i=0;i<n;i++) {
        for(int j=0;j<i;j++) {
            double cans = 0.0;
            if(r[j] <= r[i]) {
                cans += (r[j] * (r[j] - 1)) / 2;
            }
            else {
                cans += (r[i] * (r[i] - 1)) / 2;
                cans += ((r[j] - r[i]) * r[i]);
            }
            ans += (cans / r[i]) / r[j];
        }
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