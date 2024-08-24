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
 
/*
 
    I approach
    first we can try (although it can go wrong), brute force
    that is, calculate factorial for a, b and a-b
    and find fact(a) / (fact(b) * fact(a-b)) using modular arithmetic
    it would give TLE because its complexity would be O(n * (a + b + a-b)), for n <= 1e5 and b <= a <= 1e6

    OPTIMIZATION
    we can precalculate factorial of every number

    II approach
    we know that
    nCr = (a - 0) * (a - 1) * ... * (a - (b+1)) /
             1    *    2    * ... *     b

    we can run the loop till b and find the numerator and denominator using mod
    it would give TLE because its complexity would be O(n * (a + b + a-b)), for n <= 1e5 and b <= a <= 1e6


*/
string ps = "\n";

const int mod = int(1e9+7);

int power(int b, int e) {
    // if(e == 0) {
    //     return 1;
    // }

    // if(e == 1) {
    //     return b;
    // }

    // int hp = power(b, e>>1);

    int ans = 1;
    while(e) {
        if(e&1) {
            ans = (1ll * ans * b) % mod;
        }
        b = (1ll * b * b) % mod;
        e >>= 1;
    }

    return ans;
}

int inv(int n) {
    return power(n, mod-2);
}

void solve() {

    // cout << power(2, 31) << "\n";
    int maxn = int(1e6+1);
    int fact[maxn];
    fact[0] = 1;
    fact[1] = 1;

    for(int i=2;i<=maxn;i++) {
        fact[i] = (1ll * fact[i-1] * i) % mod;
    }

    int n;
    cin >> n;

    while(n--) {
        int a, b;
        cin >> a >> b;

        cout << (1ll * fact[a] * inv((1ll * fact[b] * fact[a-b]) % mod)) % mod << "\n";
    }

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