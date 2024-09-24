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
    on analysing lot of test case (by a lot means **a lot**), it looks like we have to only consider the number of sticks on even heaps, taking 0 indexing
    the reason might be that, if second person would take some sticks from heap 2 to 1, we can again keep it from 1 to 0, maintaining the same number of sticks on even indices

    Solution
    the reason is kind of correct
    if we can observe carefully, from all odd indices heaps, we can move sticks to an even index, that is from 1 to 0, 3 to 2 etc.
    we can do same in all even indices also, but not from 0 index
    so, for any person playing this game, if another person would move any stick from even to odd position, we can move same amount of stcks from the odd to even position maintaining same state for odd and even positions
    but if another person moves sticks from odd to even position, then we have to play nim game on even positions, that is, remove some number of sticks to make xor sum 0, to win

    so, the condition for winning is same as nim game, but only on the even positions
    
*/
// #define double long double

string ps = "\n";

void solve() {
    int i, n;
    cin >> n;

    int xr = 0;
    for(i=0;i<n;i++) {
        int x;
        cin >> x;

        if(i&1) {
            xr ^= x;
        }
    }

    cout << (xr ? "first" : "second") << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
 
    while(t--)
    {
        solve();
    }
 
    return 0;
}