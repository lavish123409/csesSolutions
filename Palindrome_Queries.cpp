#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
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
#define debugpdd(s, x...) cerr << s; debug(x)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#define debugpdd(s, x...)
#endif
 
/*
 
    solution
    we can use hashing for this
    we can do forward hash to calculate hash of every prefix of string
    we can do backward hash to calculate hash of every suffix of string, or we can also say that hash of every prefix of reversed string
    if some subsegment is same in both prefix and suffix, we can say that the subsegment is palindrome

    for finding hash of suffix, we can either
        - take reverse of the string and find the prefix hash, or
        - take forward hash of current string but with reversed power of primes <- much better and easier
    
    just take care of the multiplying prime at last to bring both substrings in same order
    for ex,
    forward hash = (s[0] + s[1] * p + s[2] * p^2 + .... + s[n-1] * p^(n-1)) % mod
    ans, backward hash = (s[0] * p^(n-1) + s[1] * p^(n-1-1) + s[2] * p^(n-1-2) + .... + s[n-1]) % mod

    so, when we would take substring s[0,1]
    forward hash = (s[0] + s[1] * p) % mod
    ans, backward hash = (s[0] * p^(n-1) + s[1] * p^(n-1-1)) % mod
    now as we know that we have to multiply the power (n - 1 - left_index) to substring
    for forward hash, power = (n - 1 - 0)
    but, for backward hash, power = (n - 1 - (n-1-1)), because we are increasing power from right to left, so left index for suffix would be right index and to convert index we have to do (n - 1 - right_index)
    

*/
string ps = "";

const int mod = int(1e9 + 21);

const int MAXN = int(2e5+5);
ll hfrw[MAXN], hrev[MAXN];
ll ppw[MAXN];
int p = 31;

void upd(ll bit[], int ind, ll val) {
    for(ind++; ind < MAXN; ind += (ind & -ind)) {
        bit[ind] = (bit[ind] + val) % mod;
    }
}

ll qry(ll bit[], int ind) {
    ll ans = 0ll;
    for(ind++; ind; ind -= (ind & -ind)) {
        ans = (ans + bit[ind]) % mod;
    }

    return ans;
}

struct {
    ll bit[MAXN];

    void upd(int ind, ll val) {
        for(ind++; ind < MAXN; ind += (ind & -ind)) {
            bit[ind] = (bit[ind] + val) % mod;
        }
    }
    
    ll qry(int ind) {
        ll ans = 0ll;
        for(ind++; ind; ind -= (ind & -ind)) {
            ans = (ans + bit[ind]) % mod;
        }

        return ans;
    }
} pre, suf;

void solve() {
    
    int i, n, m;
    cin >> n >> m;

    string s;
    cin >> s;
    string r = s;
    reverse(r.begin(), r.end());
    // cout << s << " : " << r << "\n";

    ppw[0] = 1;
    for(i=1;i<n;i++) {
        ppw[i] = (ppw[i-1] * p) % mod;
    }

    for(i=0;i<n;i++) {
        // upd(hfrw, i, (1ll * (s[i] - 'a') * ppw[i]) % mod);
        // upd(hfrw, i, (1ll * (s[i] - 'a')) % mod);
        // cout << s[i] << " : " << s[i]-'a' << " , " << s[n-1-i] << " : " << s[n-1-i] - 'a' << "\n";
        // upd(hfrw, i, (1ll * (s[i] - 'a')) % mod);
        // upd(hrev, n - i - 1, (1ll * (s[i] - 'a') * ppw[n - i - 1]) % mod);
        // upd(hrev, i, (1ll * (r[i] - 'a') * ppw[i]) % mod);
        // upd(hrev, i, (1ll * (r[i] - 'a')) % mod);
        // upd(hrev, n - i - 1, (1ll * (s[i] - 'a')) % mod);

        pre.upd(i, (ppw[i] * (s[i] - 'a')) % mod);
        suf.upd(i, (ppw[n - 1 - i] * (s[i] - 'a')) % mod);
    }

    // for(int l=1;l<=n;l++) {
    //     for(i=0; i+l <= n; i++) {
    //         ll chash = (qry(hfrw, i+l-1) + mod - qry(hfrw, i-1)) % mod;
    //         ll crhsh = (qry(hrev, i+l-1) + mod - qry(hrev, i-1)) % mod;
    //         // cout << l << " : " << i << " , " << i+l-1 << " = " << chash << " <- hsh\n";
    //         // cout << l << " : " << n-i-1 << " , " << n-i+l-2 << " = " << crhsh << " <- rhsh\n";
    //         cout << l << " : " << i << " , " << i+l-1 << " = " << chash << " ; " << crhsh << "\n";
    //     }
    // }

    // for(i=0;i<n;i++) {
    //     // cout << ((qry(hfrw, i) + mod - qry(hfrw, i-1)) * ppw[n-1-i]) % mod << " , ";
    //     cout << ((pre.qry(i) + mod - pre.qry(i-1))) % mod << " , ";
    // }
    // cout << "\n";
    
    // for(i=0;i<n;i++) {
    //     // cout << ((qry(hrev, i) + mod - qry(hrev, i-1)) * ppw[n-1-i]) % mod << " , ";
    //     cout << ((suf.qry(i) + mod - suf.qry(i-1))) % mod << " , ";
    // }
    // cout << "\n";
    // cout << ((pre.qry(1))) % mod << " , ";
    // cout << ((suf.qry(1))) % mod << "\n";
    // cout << ((pre.qry(1) * ppw[n-1-0])) % mod << " , ";
    // cout << ((suf.qry(1) * ppw[n-1-(n-1-1)])) % mod << "\n";

    while(m--) {
        int t;
        cin >> t;

        if(t == 1) {
            int ind;
            char x;
            cin >> ind >> x;
            ind--;

            // ll ol = (1ll * (s[ind] - 'a') * ppw[ind]) % mod;
            // ll nw = (1ll * (x - 'a') * ppw[ind]) % mod;
            // // ll ol = (1ll * (s[ind] - 'a')) % mod;
            // // ll nw = (1ll * (x - 'a')) % mod;
            // upd(hfrw, ind, (nw - ol + mod) % mod);
            // s[ind] = x;
            pre.upd(ind, (1ll * (x - s[ind] + mod) * ppw[ind]) % mod);
            
            // ind = n-1 - ind;
            // ol = (1ll * (r[ind] - 'a') * ppw[ind]) % mod;
            // nw = (1ll * (x - 'a') * ppw[ind]) % mod;
            // // ol = (1ll * (r[ind] - 'a')) % mod;
            // // nw = (1ll * (x - 'a')) % mod;
            // upd(hrev, ind, (nw - ol + mod) % mod);
            // r[ind] = x;
            suf.upd(ind, (1ll * (x - s[ind] + mod) * ppw[n - ind - 1]) % mod);
            s[ind] = x;
        }
        else {
            int st, en;
            cin >> st >> en;
            st--, en--;

            // ll fh = (qry(hfrw, en) - qry(hfrw, st-1) + mod) % mod;
            // // cout << s.substr(st, en-st+1) << "\n";
            // ll rv = (qry(hrev, n-1-st) - qry(hrev, n-1-en-1) + mod) % mod;
            // // cout << r[n-1-en] << " : " << r[n-1-st] << "\n";
            // // cout << r.substr(n-1-en, n-1-st - (n-1-en) + 1) << "\n";
            // // cout << st << " : " << en << "\n";
            // // cout << n-en-1 << " : " << n-st-1 << "\n";
            // // cout << qry(hfrw, en) << " : " << qry(hfrw, st-1) << "\n";
            // // cout << qry(hrev, n-1-st) << " : " << qry(hrev, n-1-en-1) << "\n";
            // // cout << fh << " : " << rv << "\n";

            // fh = (fh * ppw[n-st-1]) % mod;
            // // rv = (rv * ppw[n-st-1]) % mod;
            // rv = (rv * ppw[en]) % mod;
            // // cout << fh << " : " << rv << "\n";

            ll fh = (pre.qry(en) - pre.qry(st-1) + mod) * ppw[n-1 - st] % mod;
            ll rv = (suf.qry(en) - suf.qry(st-1) + mod) * ppw[n-1 - (n-1-en)] % mod;
            // cout << fh << " : " << rv << "\n";
            cout << (fh == rv ? "YES" : "NO") << "\n";
        }
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