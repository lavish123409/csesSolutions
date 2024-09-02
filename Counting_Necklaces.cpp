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
    we can see in the explanation of fermat little theorem -> https://youtu.be/OoQ16YCYksw?feature=shared
    that, for all i < n, if n % i == 0, then the period for that necklace would be smaller, that is the number of different necklaces which would be considered same would be less than n
    otherwise, if n % i != 0, then the period for that necklace would be n

    first, we would get total number of arrangements that we can make, which is m^n
    now, for every i < n, we can see if n % i == 0
        - we should subtract all the arrangements having period of i, and add the unique ways to the answer
        - total number of arrangements would be mCi, because we should choose a combination of m colors for i positions
            - we cannot repeat colors because we would have already covered that case in lesser i values, for ex, for m=3 and i=2, we would have covered 11 case in i=1
            - we cannot take permutations because for ex, for m=3 and i=2, 31 would be considered same as 13
        - and the number of unique arrangements would be (total arrangements)/i, because they have a period of i
    we should also check whether i is prime or not, because the period for 4 and 2 would be 2 only

    at last, we would add the unique arrangements for remaining arrangements which would be (total arrangements)/n, because they have a period of i

    WA1
    while calculating total number of arrangements for i < n, it would be mPi, because those would come in total arrangments
    for ex, for m=3 and i=3, the total number of arrangments would be mPi = 3P3 = 6, i.e, 
        123 132 213 231 312 321,
        but unique arrangements would be mPi / i = 3P3 / 3 = 2
            {123 231 312}
            {132 321 213}
        and mCi would be 3C3 = 1

    RE and WA2
    didn't realised that we have to find mPi, so we woud need to find factorial till m and not n [don't know whether it worked or not]

    Solution
    it is based on burnside
    not able to understand much
    explanation -> https://www.geeksforgeeks.org/orbit-counting-theorem-or-burnsides-lemma/

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

int ncr(int fact[], int n, int r) {
    return (1ll * fact[n] * inv((1ll * fact[n-r]) % mod)) % mod;

}

void solve() {

    int n, m;
    cin >> n >> m;

    vector<bool> isPrime(n, 1);
    int fact[max(n, m)+1];
    
    fact[0] = fact[1] = 1;
    for(int i=2;i<=max(m, n);i++) {
        fact[i] = (1ll * i * fact[i-1]) % mod;
    }

    for(int i=2;i<n;i++) {
        if(isPrime[i]) {
            for(int j=2*i; j<n; j += i)
                isPrime[j] = 0;
        }
    }
    // for(int i=1;i<n;i++) {
    //     cout << i << " : " << isPrime[i] << " , ";
    // }
    // cout << "\n";

    int tans = pwr(m, n);
    int ans = 0;
    // for(int i=1;i<n;i++) {
    //     // debug(isPrime[i]);
    //     // cerr << i << " : " << isPrime[i] << "\n";
    //     // if(isPrime[i] && n % i == 0 && i <= m) {
    //     if(n % i == 0 && i <= m) {
    //         // int ilp = (1ll * i * ncr(fact, m, i)) % mod;
    //         int ilp = ncr(fact, m, i);
    //         debug(i, m, ilp);
    //         tans = (1ll * tans - (1ll * ilp) % mod + mod) % mod;
    //         ans = (1ll * ans + (1ll * ilp * inv(i)) % mod) % mod;
    //     }
    //     debug(tans, ans);
    // }

    // ans = (1ll * ans + (1ll * tans * inv(n)) % mod) % mod;

    for(int i=0;i<n;i++) {
        ans = (1ll * ans + pwr(m, __gcd(n, i))) % mod;
    }

    ans = (1ll * ans * inv(n)) % mod;

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

// C++ program for implementing the
// Orbit counting theorem
// or Burnside's Lemma

// #include <bits/stdc++.h>
// using namespace std;

// // Function to find result using
// // Orbit counting theorem
// // or Burnside's Lemma
// void countDistinctWays(int N, int M)
// {

// 	int ans = 0;

// 	// According to Burnside's Lemma
// 	// calculate distinct ways for each
// 	// rotation
// 	for (int i = 0; i < N; i++) {

// 		// Find GCD
// 		int K = __gcd(i, N);
//         cout << i << " , ";
//         cout << K << " : ";
// 		ans += pow(M, K);
//         cout << pow(M, K) << " - ";
//         cout << ans << "\n";
// 	}

// 	// Divide By N
// 	ans /= N;

// 	// Print the distinct ways
// 	cout << ans << endl;
// }

// // Driver Code
// int main()
// {

// 	// N stones and M colors
// 	// int N = 4, M = 3;
//     int N, M;
//     cin >> N >> M;

// 	// Function call
// 	countDistinctWays(N, M);

// 	return 0;
// }
