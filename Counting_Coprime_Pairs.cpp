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
    
    int i, n;
    cin >> n;

    int arr[n];
    int mx = 0;
    for(i=0;i<n;i++) {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }

    // vector<bool> isPrime(mx+1, 1);
    // vector<int> inArray(mx+1);
    // for(i=0;i<n;i++) {
    //     inArray[arr[i]]++;
    // }

    // isPrime[0] = 0;
    // isPrime[1] = 0;

    // ll ans = (1ll * n * (n-1)) / 2;
    // set<int> badno;
    // for(i=2;i<=mx;i++) {
    //     ll cpairs = 0;
    //     if(isPrime[i]) {
    //         // if(inArray[i]) {
    //         //     cpairs = 1;
    //         // }
    //         cpairs += inArray[i];
    //         for(int j=2*i; j <= mx; j+=i) {
    //             if(isPrime[j]) {
    //                 // if(inArray[j]) {
    //                 //     cpairs++;
    //                 // }
    //                 cpairs += inArray[j];
    //                 isPrime[j] = 0;
    //             }
    //         }
    //     }
    //     cout << i << " : " << cpairs << "\n";
    //     ans -= ((1ll * cpairs * (cpairs - 1)) / 2);
    // }

    // cout << ans << "\n";

    vector<vector<int>> primeFactors(mx+1);
    int mxpf = 0;
    for(i=2;i<=mx;i++) {
        if(primeFactors[i].size() == 0) {
            primeFactors[i].push_back(i);
            for(int j=2*i;j<=mx;j+=i) {
                primeFactors[j].push_back(i);
            }
        }
        mxpf = max(mxpf, int(primeFactors[i].size()));
    }

    // for(i=2;i<=mx;i++) {
    //     cout << i << " : ";
    //     for(int pf : primeFactors[i]) {
    //         cout << pf << " ";
    //     }
    //     cout << "\n";
    // }

    int contri[mx+1][mxpf+1];
    memset(contri, 0, sizeof(contri));
    for(i=0;i<n;i++) {
        int nop = primeFactors[arr[i]].size();
        for(int sbst=1; sbst < (1 << nop); sbst++) {
            int prod = 1;
            int cnt = 0;
            for(int j=0;j<nop;j++) {
                if(sbst & (1 << j)) {
                    prod *= primeFactors[arr[i]][j];
                    cnt++;
                }
            }

            contri[prod][cnt]++;
        }
    }

    // for(i=0;i<=mx;i++) {
    //     for(int j=1;j<=mxpf;j++) {
    //         cout << i << " , " << j << " - " << contri[i][j] << "; ";
    //     }
    //     cout << "\n";
    // }

    ll ans = (1ll * n * (n-1)) / 2;
    // int validPairs = 0;
    for(i=0;i<=mx;i++) {
        for(int j=1;j<=mxpf;j++) {
            // int cnum = contri[i][j];
            int validPairs = contri[i][j];
            if(j&1) {
                ans -= ((1ll * validPairs * (validPairs - 1)) / 2);
                // validPairs += cnum;
            }
            else {
                ans += ((1ll * validPairs * (validPairs - 1)) / 2);
                // validPairs -= cnum;
            }
        }
    }
    // cout << validPairs << "\n";

    // cout << ans - (1ll * validPairs * (validPairs-1)) / 2 << "\n";
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