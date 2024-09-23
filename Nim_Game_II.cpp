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
    if we ould observe carefully, then we can see that for
        n=1, first person would win, because he can take the 1 stick and finish the game
        n=2, first person would win, because he can take all the 2 sticks and finish the game
        n=3, first person would win, because he can take all the 3 sticks and finish the game
        n=4, second person would win, because whatever number of sticks first person would take, it would leave second person in the winning state mentioned above
        n=5, first person can take 1 stick, and leave the second person in losing state of 4 sticks

    and from nim game analysis (or sprague-grundy theorem), we know that we can replace all heaps of sticks with the xor sum number of sticks in one heap
    so, we can check whether the xor sum of heaps is divisible by 4 or not
    if it is then, then second person would win
    otherwise, first person would win
    
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

        xr ^= x;
    }

    cout << (xr % 4 ? "first" : "second") << "\n";
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