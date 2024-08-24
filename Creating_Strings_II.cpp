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
    it looks like the problem told in 11th class
    we are given some characters and we have to form a string from it
    now, if there are n characters we can form n! characters
    and if if there is some character with frequency > 1
    then, divide the ans by (freq[ch])!, the sequence of those characters, that is {ch ch ch ...freq times... ch}, can be used to make strings in (freq[ch])! ways
    so, we would have to divide that from the total number of ways, for every character

*/
string ps = "\n";

const int mod = int(1e9+7);

int power(int b, int e) {
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
    int maxn = int(1e6)+1;
    int fact[maxn];

    fact[0] = 1;
    fact[1] = 1;

    for(int i=2;i<=maxn;i++) {
        fact[i] = (1ll * i * fact[i-1]) % mod;
    }

    string s;
    cin >> s;

    int i, n;
    n = s.size();
    int frq[26] = {0};

    for(i=0;i<n;i++) {
        frq[s[i] - 'a']++;
    }

    int ans = fact[n];
    for(i=0;i<26;i++) {
        if(frq[i] > 1) {
            ans = (1ll * ans * inv(fact[frq[i]])) % mod;
        }
    }

    cout << ans << "\n";

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