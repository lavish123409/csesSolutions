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
 
    I approach
    let's think of number of ways, we can make a string of n characters where m characters string is a substring
    first of all, we can fill n places with 26 characters = 26^n ways
        _  _  _  ... _  _  _  -> n times
        26 26 26     26 26 26
    then, for m characters to be substring, we can fill m positions with those characters and rest characters with other 26 characters
        x  x  x ... x  x  _  _  _  _  _
        1  1  1     1  1  26 26 26 26 26
            m times         (n - m) times
    so, in 26^(n-m) ways we can have n strings in which m character string is substring at first position
    then, we can shift that string (n - m + 1) times, so total ways = 26^n - ((n - m + 1) * 26^(n - m))

    now, coming to question
    we would have (n - m) remaining characters to fill around m character string
    some of them, would be before the m string and some would be after it
    let us take l characters which are before m string
    and, for these l characters we have to find the number of strings we can make in which m string is not a substring fo which we formulated the formula earlier
    and we have to also consider those strings, which can form m string from the prefix of m string
    for this, we would have to consider all prefix length which is also the suffix and subtract those strings also
    for ex, s = abcabcabcabc
    and we have to fill 10 characters before s
    then, we would have to subtract
        _ _ _ _ _ _ _ a b c abcabcabcabc
        _ _ _ _ a b c a b c abcabcabcabc
        _ a b c a b c a b c abcabcabcabc
    all these strings because they are making that string

    similarly, we have to handle back of the string also

    PROBLEM
    I think we are over counting it
    suppose string is s = abcabc
    and we have to fill 7 places before s
    then, while calculating number of n strings in which m string is not there would be 26^7 - (7 - 6 + 1) * 26^1
    now, for prefixes we would calculate
    number of strings like this _ _ _ _ a b c abcabc
    but 26 of the strings would have already been calculated in
    number of strings like this _ a b c a b c abcabc
    and we would overcount them

*/
string ps = "";

const int mod = int(1e9 + 7);

// int power(int b, int e) {
//     int ans = 1;
//     while(e) {
//         if(e&1) b = (1ll * ans * b) % mod;
//         b = (1ll * b * b) % mod;
//         e >>= 1;
//     }

//     return ans;
// }

int power(int b, int e) {
    if(e == 0) {
        return 1;
    }

    if(e == 1) {
        return b;
    }

    int hp = power(b, e>>1);
    hp = (1ll * hp * hp) % mod;
    if(e&1) {
        hp = (1ll * hp * b) % mod;
    }

    return hp;
}

int findWays(int n, int m) {
    int ans = power(26, n);
    ans = (ans - (1ll * (n - m + 1) * power(26, n-m)) % mod + mod) % mod;
    return ans;
}

const int MAXN = 1001;
const int MAXM = 101;
const int MAXK = 26;
int lps[MAXM];
ll dp[MAXN][MAXM];
string s;

int recurse1(int in, int mmpl, int n, int m, int nrss) {
    if(in == n) {
        return nrss > 0;
    }

    ps.push_back('\t');
    debugpdd(ps, in, mmpl, nrss);

    int ans = 0;

    // matching case
    if(mmpl+1 >= m) {
        ans += recurse1(in+1, 0, n, m, nrss+1);
    }
    else {
        ans += recurse1(in+1, mmpl+1, n, m, nrss);
    }
    debugpdd(ps, "lans : ", ans);

    // non matching case
    set<char> uc;
    uc.insert(s[mmpl]);
    mmpl = lps[mmpl - 1];
    while(mmpl > 0) {
        uc.insert(s[mmpl]);
        ans += recurse1(in+1, lps[mmpl-1], n, m, nrss);
        mmpl = lps[mmpl-1];
    }
    debugpdd(ps, uc);
    // uc.insert(s[0]);
    // ans += recurse1(in+1, 1, n, m, nrss);
    ans += (26 - uc.size()) * recurse1(in+1, 0, n, m, nrss);

    // ans += 25 * recurse1(in+1, max(0, lps[mmpl-1]), n, m, nrss);

    // ans += recurse1(in+1, mmpl > 0 ? lps[mmpl-1] : 0, n, m, nrss);
    // ans += 24 * recurse1(in+1, 0, n, m, nrss);
    debugpdd(ps, "tans : ", ans);
    ps.pop_back();

    return ans;

}

ll recurse(int in, int mmpl, int n, int m) {
    if(dp[in][mmpl] != -1) {
        return dp[in][mmpl];
    }

    if(in == n) {
        return dp[in][mmpl] = mmpl == (int)s.size() ? 1 : 0;
    }

    if(mmpl == (int)s.size()) {
        return dp[in][mmpl] = (1ll * MAXK * recurse(in+1, mmpl, n, m)) % mod;
    }

    int k;
    ll ans = 0ll;
    for(k=0;k<MAXK;k++) {
        int j = mmpl;
        while(j > 0 && s[j] != 'A' + k) {
            j = lps[j-1];
        }
        if(s[j] == 'A' + k) j++;

        ans = (ans + recurse(in+1, j, n, m)) % mod;
    }

    return dp[in][mmpl] = ans;
}

void solve() {
    int i, n, m;
    cin >> n;

    // string s;
    cin >> s;
    m=s.size();

    for(i=1;i<m;i++) {
        int j = lps[i-1];
        while(j > 0 && s[i] != s[j]) {
            j = lps[j-1];
        }

        if(s[i] == s[j]) {
            j++;
        }

        lps[i] = j;
    }
    memset(dp, -1, sizeof(dp));

    cout << recurse(0, 0, n, m) << "\n";
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