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
    we can use the catalan number technique
    from the explanation, https://youtu.be/Rz01xHKrz8k?feature=shared
    we know the catalan number is 
        the number of ways we can reach (n,n) from (0,0) - the number of ways we can reach (n+1,n-1) from (0,0)
    
    but, here we have a different starting point from (0,0) which would be (number of open brackets, number of closed brackets) and total number would also decrease by (number of open brackets + number of closed brackets)
    so, the answer would be (n-tl)C(n/2 - min(obl, cbl)) - (n-tl)C(n/2 - min(obl, cbl)-1)

    WA1
    missed this test case
        8
        ())(

*/
string ps = "\n";

const int mod = int(1e9+7);

int pwr(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans = (1ll * ans * b) % mod;
        b = (1ll * b * b) % mod;
        e >>= 1;
    }

    return ans;
}

int inv(int n) {
    return pwr(n, mod-2);
}

void solve() {

    int n;
    cin >> n;

    string s;
    cin >> s;
    if(n&1) {
        cout << "0\n";
        return;
    }

    int tl = s.size();
    // n -= tl;
    int obl=0, cbl=0;
    for(int i=0;i<tl;i++) {
        obl += (s[i] == '(');
        cbl += (s[i] == ')');
        if(cbl > obl) {
            cout << "0\n";
            return;
        }
    }

    if(cbl > obl || obl * 2 > n) {
        debug(obl * 2 > n);
        cout << "0\n";
        return;
    }

    int mbl = min(obl, cbl);
    debug(mbl, n/2-mbl);

    int ans = 1;
    for(int r=0;r<n/2-mbl;r++) {
        ans = (1ll * ans * (n - tl - r)) % mod;
        ans = (1ll * ans * inv(r+1)) % mod;
    }
    debug(ans);
    
    int bad = 1;
    // mbl = min(obl-1, cbl+1);
    mbl += (mbl == cbl ? -1 : 1);
    debug(mbl, n/2-mbl);
    for(int r=0;r<n/2-mbl;r++) {
        bad = (1ll * bad * (n - tl - r)) % mod;
        bad = (1ll * bad * inv(r+1)) % mod;
    }
    debug(bad);

    cout << (1ll * ans - bad + mod) % mod << "\n";

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