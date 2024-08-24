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
 
    we know that the numbers, which a prime number p would divide in the range [1,n] is floor(n/p)
    so, we can calculate the answer by adding n/p_i for every given p_i
    but, in this process we would over calculate for values p_i * p_j, where i != j
    so, we can calculate the answer by subtracting n/(p_i * p_j) for every given p_i * p_j
    but, in this process we would under calculate for values p_i * p_j * p_l, where i != j && j != l && l != i
    and, so on we would have to add and then subtract from the answer for every subset of k prime numbers of 1, 2, 3.... prime numbers in the subset

    TLE
    forgot to remove cerr statements

    WA
    long long overflow
    if we would multiply prime numbers <= 10^18 for k=20 times
    it would overflow


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
    
    // unsigned int v; // current permutation of bits 
    // unsigned int w; // next permutation of bits

    
    // for(int v=3; v< 16;) {

    //     cout << v << " : ";
    //     int t = v | (v - 1); // t gets v's least significant 0 bits set to 1
    //     // Next set to 1 the most significant bit to change, 
    //     // set to 0 the least significant ones, and add the necessary 1 bits.
    //     v = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));  
    //     cout << v << "\n";

    // }

    ll n;
    int i, k;
    cin >> n >> k;

    ll p[k];
    for(i=0;i<k;i++) {
        cin >> p[i];
    }

    ll ans = 0ll;
    int sign = 1;
    // for(ll sbst=1ll; sbst < (1ll << k); sbst = (sbst << 1) + 1) {
    //     ll csbst = sbst;
    //     while(1) {
    //         unsigned long long prod = 1ll;
    //         for(i=0;i<k;i++) {
    //             if(csbst & (1ll << i)) {
    //                 if((prod * p[i]) / p[i] != prod) {
    //                     prod = n+1;
    //                     break;
    //                 }
    //                 debug(p[i], prod, 1ull * prod * p[i]);
    //                 prod *= p[i];
    //                 debug(i, p[i], prod);
    //             }
    //         }

    //         ans += (1ll * sign * (n / prod));
    //         // cerr << bitset<8>(csbst) << " , ";
    //         // debug(ans, sign, prod);
    //         ll t = csbst | (csbst - 1); // t gets csbst's least significant 0 bits set to 1
    //         // Next set to 1 the most significant bit to change, 
    //         // set to 0 the least significant ones, and add the necessary 1 bits.
    //         csbst = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(csbst) + 1));

    //         if(csbst >= (1ll << k)) break;
    //     }
    //     sign *= -1;
    // }
    for(ll sbst=1ll; sbst < (1ll << k); sbst++) {
        // vector<ll> v;
        ll prod = 1ll;
        int cnt = 0;
        for(i=0;i<k;i++) {
            if(sbst & (1ll << i)) {
                if(prod > n / p[i]) {
                    prod = n+1;
                    break;
                }
                prod *= p[i];
                cnt++;
            }
        }

        if(cnt&1) {
            ans += n / prod;
        }
        else {
            ans -= n / prod;
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