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
 
    we know that every divisor of a number can be uniquely represented by combinations of multiplication of powers of its prime factors
    for ex, 12 = 2^0*3^0 , 2^0*3^1 , 2^1*3^0 , 2^1*3^1 , 2^2*3^0 , 2^2*3^1

    so, count of divisors can be found by \product(power of prime factor p_i + 1)
    that is, for 12 => (2 + 1) * (1 + 1)
                        for 2     for 3

    for addition, we can write it as
    2^0*3^0 + 2^0*3^1 + 2^1*3^0 + 2^1*3^1 + 2^2*3^0 + 2^2*3^1 = (2^0 + 2^1 + 2^2) * (3^0 + 3^1)
    so, addition would be 
    \product(for every prime factor, the sum of G.P. (p_i^0 + p_i^1 + ... + p_i^maxPower))

    for multiplication, we would have to multiply all divisors
    = 2^0*3^0 * 2^0*3^1 * 2^1*3^0 * 2^1*3^1 * 2^2*3^0 * 2^2*3^1
    = 2^(0 + 0 + 1 + 1 + 2 + 2) * 3^(0 + 0 + 0 + 1 + 1 + 1)
    = 2^(2 * (0 + 1 + 2))
    * 3^(3 * (0 + 1))
    = p_i^(product of other prime factors powers(i.e, 3 in this case) * \sum(0 till power of current prime factor(i.e, 2)))
    * p_{i+1}^(product of other prime factors powers(i.e, 2 in this case) * \sum(0 till power of current prime factor(i.e, 3)))
    we can use this fact
        a^(b mod m-1) mod m = a^(b) mod m
    if b becomes too large

    MISTAKE
    missed a trick
    we know that (a^b)^c = a^(b*c)
    so, we can find 
        p_i^(((k_0 + 1) * (k_1 + 1) * ... * (k_i + 1) * (k_{i+1} + 1) * ... (k_n + 1)) * \sum(1 .. k_i + 1))
    by this method, where P_i is product till ith prime factor and C_i is count of prime factors till now, i.e, ((k_0 + 1) * ... * (k_{i-1} + 1))
        P_i = (P_{i-1})^(k_i + 1) * (p_i ^ ((k_i * (k_i + 1)) / 2) mod (m-1)) ^ C_{i-1})
    in this way, the previous powers also would get multiplied by right amount, when we would do P_{i-1})^(k_i + 1) for every prime factor p_i


*/
string ps = "\n";

const int mod = int(1e9+7);

int mulm(int a, int b, int mod) {
    a %= mod;
    b %= mod;

    return (1ll * a * b) % mod;
}

int power(ll b, ll e, int mod) {
    if(e == 0) {
        return 1;
    }

    if(e == 1) {
        return b;
    }

    int hp = power(b, e>>1, mod);
    hp = (1ll * hp * hp) % mod;
    if(e&1) {
        hp = (1ll * hp * b) % mod;
    }

    return hp;
}

void solve() {
    
    int i, n;
    cin >> n;

    array<int, 2> vals[n];
    for(i=0;i<n;i++) {
        cin >> vals[i][0] >> vals[i][1];
    }

    int count=1;
    int tpw=1;
    for(i=0;i<n;i++) {
        count = mulm(count, vals[i][1] + 1, mod);
        tpw = mulm(tpw, 1 + vals[i][1], mod-1);
    }

    cout << count << " ";

    int addn = 1;
    for(i=0;i<n;i++) {
        int pf = vals[i][0];
        int pw = vals[i][1];

        addn = mulm(addn, power(pf, pw+1, mod) - 1 + mod, mod);
        addn = mulm(addn, power(pf - 1, mod-2, mod), mod);
        debug(i, pf, pw, addn);
    }

    cout << addn << " ";

    int mult = 1, divCount = 1;
    for(i=0;i<n;i++) {
        mult = power(mult, vals[i][1] + 1, mod);
        int cprod = power(vals[i][0], (1ll * vals[i][1] * (vals[i][1] + 1)) / 2, mod);
        cprod = power(cprod, divCount, mod);

        mult = mulm(mult, cprod, mod);
        divCount = mulm(divCount, vals[i][1] + 1, mod-1);
    }

    cout << mult << "\n";

    // for(i=0;i<n;i++) {

    // }

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