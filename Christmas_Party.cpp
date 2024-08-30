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
 
    Solution
    it is a standard problem of derangements
    
    I technique
    either, we can use recursive formula
        D(n) = (n-1) * (D{n-1} + D(n-2))
    which comes from the fact that,
        - suppose there are p1, p2, ... pn persons and g1, g2, ... gn gifts
        - let's say p1 got gi gift
        - now, there are 2 cases
            - if pi would get g1, then we can find derangements on rest n-2 persons for n-2 gifts
            - if pi would not get g1, then for every n-1 persons, there is only one gift that they cannot get, for pi it cannot get g1 and for other pj != p1 && pj != pi, it cannot get gj, so now we would have to solve for n-1 persons and gifts

    II technique
    we can use inclusion exclusion principle
    its a good alternative to check the not version of given problem, and think about it to solve
    here, we want that any number should not come to its own position, then we can write it as
        all = good + bad
    where, all -> all possible arrangements
    and bad -> 1 comes on 1st position || 2 comes on 2nd position || .... || n comes on nth position

    we can use inclusion exclusion principle to find bad ways
        - we would use following notation
            W(1->1), meaning 1 goes to 1st position
        W(1->1 || 2->2 || ... || n->n) = W(1->1) + W(2->2) + ... + W(n->n)
                                       - W(1->1 && 2->2) + W(2->2 && 3->3) + ... + W(n-1->n-1 && n->n)
                                       + W(1->1 && 2->2 && 3->3) + ... + W(n-2->n-2 && n-1->n-1 && n->n)
                                       ...
                                      +- W(1->1 && 2->2 && 3->3 ... && n->n)

                                      = nC1 * (n-1)! + nC2 * (n-2)! + ... + nCn * (0)!


*/
string ps = "\n";

const int mod = int(1e9+7);

int power(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans = (1ll * ans * b) % mod;
        b = (1ll * b * b) % mod;
        e >>= 1;
    }

    return ans;
}

int inv(int n) {
    return power(n, mod-2);
}

void solve() {
    int i, n;
    cin >> n;

    // int fact[n+1] = {0};
    // fact[0] = 1;
    // fact[1] = 1;

    // for(i=2;i<=n;i++) {
    //     fact[i] = (1ll * fact[i-1] * i) % mod;
    // }

    // auto ncr = [&](int n, int r) {
    //     return (1ll * fact[n] * inv((1ll * fact[r] * fact[n-r]) % mod)) % mod;
    // };

    // // int ans = fact[n];
    // int ans = 0;
    // debug(ans);
    // // int bad = 0;
    // int sign = 1;
    // for(i=2;i<=n;i++) {
    // // for(i=1;i<=n;i++) {
    //     // int cans = fact[n-i];
    //     // debug(i, cans);
    //     // cans = (1ll * cans * ncr(n, i)) % mod;
    //     // debug(i, cans);
    //     // bad = (1ll * bad + sign * cans + mod) % mod;
    //     // sign *= -1;
    //     // debug(i, cans);
    //     ans = (1ll * ans + sign * (1ll * fact[n] * inv(fact[i])) % mod + mod) % mod;
    //     sign *= -1;
    // }
    // // debug(ans, bad);

    // // cout << (1ll * ans - bad + mod) % mod << "\n";
    // cout << ans << "\n";

    int ans[n+1] = {0};
    ans[1] = 0;
    ans[2] = 1;

    for(i=3;i<=n;i++) {
        ans[i] = (1ll * (i-1) * (1ll * ans[i-1] + ans[i-2]) % mod) % mod;
    }

    cout << ans[n] << "\n";
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