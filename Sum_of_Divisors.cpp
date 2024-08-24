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
 
/*
 
    WA1
    I was thinking that while calculating right sum and left sum, left sum would always be less than the right sum
    but it can turn out that right sum after mod can become less than left sum

*/
string ps = "\n";

const int mod = int(1e9+7);
const int inv2 = 500000004;


int gcd(int a, int b) {
    if(b == 0) return a;

    return gcd(b, a%b);
}

// ll getSum()

// int power(int b, int e) {
//     if(e == 0) {
//         return 1;
//     }

//     if(e == 1) {
//         return b;
//     }

//     int hp = power(b, e>>1);
//     hp = (1ll * hp * hp) % mod;
//     if(e&1) {
//         hp = (1ll * hp * b) % mod;
//     }

//     return hp;
// }

// int getSum(ll a, ll b) {
//     ll rsum = (1ll * b * (b+1)) % mod;
//     ll lsum = (1ll * a * (a-1)) % mod;
//     debug(b+1, (1ll * b * (b+1)));
//     debug(lsum, rsum, (1ll * (1ll * rsum - lsum + mod) * inv2));

//     return ((rsum - lsum + mod) * inv2) % mod;
// }

long long total_sum(long long start, long long end) {
    debug(((((end - start + 1) % mod) * ((start + end) % mod) % mod) *
	        inv2 % mod));
	return ((((end - start + 1) % mod) * ((start + end) % mod) % mod) *
	        inv2 % mod);
}

void solve() {
    
    ll n;
    cin >> n;

    // cout << int(n * log(1.0l + 2.0l * n)) << "\n";
    // for(int i=1;i<=n;i++) {
    //     for(int j=1;j<=i;j++) {
    //         cout << i / j << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << power(2, mod-2) << "\n";
    int ans=0;
    for(ll i=1;i<=n;){
        ll q = n / i;
        ll next = n / q + 1;
        ans += (q % mod * total_sum(i, next-1)) % mod;
        // debug(i, next, ans);
        ans %= mod;
        i = next;
    }
    // for(ll i=1;i<=(ll)(1e12);i++) {
    //     if(getSum(1, i) != total_sum(1, i)) {
    //         cout << i << " ";
    //         break;
    //     }
    // }
    // cout << "\n";
    // debug(getSum(1, 3037000500));
    // debug(total_sum(1, 3037000500));

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