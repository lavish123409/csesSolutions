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

// tip: its a good alternative to check the not version of given problem, and think about it to solve first
// for ex, Christmas party
 
/*
 
    I appraoch
    I was thinking that it is related to that question, in which we have to find non-negative solutions for the equation
        x1 + x2 + ... xn = sumVal
    just, the difference is that here, n can also change from sumVal (indicating, 1+1+1+1...+1 = sumVal) to sumVal / 6 (indicating, 6+6+6+6...+6 = sumVal)

    for given constraints on n <= 1e18, we can see in this approcach that
    we would have to calculate the factorial of n, in order to calculate multicombination of (n,r)
    which would not be possbile even with the mod, because we would have to do n multiplying operations

    II approach
    while printing correct value for sample test case by dp(commented in this code), I realised that to calculate answer for n, we just have to calculate
        ans(n) = ans(n-1) + ans(n-2) + ans(n-3) + ans(n-4) + ans(n-5) + ans(n-6), for n > 6
    
    so now, we know that in a recurrence relation, we can use matrix exponentiation technique
    so, it is just an extension of previous problem
    in this case, we just have to use 6x6 matrix, similar to fibonacci for representing above recurrence
    and solve it using above matrix exponentiation by raising it to power n-6, as we can calculate from dp till 6 (till then above recurrence would not be followed)
*/

string ps = "\n";

const int mod = int(1e9+7);

vector<vector<ll>> matMul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
    int i, j, k;
    int n=a.size();

    vector<vector<ll>> ans(n, vector<ll>(n));
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            for(k=0;k<n;k++) {
                ans[i][j] += a[i][k] * b[k][j];
                ans[i][j] %= mod;
            }
        }
    }

    return ans;
}

vector<vector<ll>> matExp(vector<vector<ll>>& mat, ll e) {
    int i, j, n = mat.size();
    vector<vector<ll>> ans(n, vector<ll>(n));

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            ans[i][j] = (i == j);
        }
    }

    // cout << "matexp : \n";
    // for(i=0;i<n;i++) {
    //     for(j=0;j<n;j++) {
    //         cout << ans[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    while(e) {
        if(e&1) {
            ans = matMul(ans, mat);
        }
        mat = matMul(mat, mat);
        e >>= 1;
    }

    return ans;
}

void solve() {
    int i, j;
    ll n;
    cin >> n;

    // int dp[n+1] = {0};
    // dp[0] = 1;

    // for(i=1;i<=n;i++) {
    //     for(j=1;j<=6;j++) {
    //         if(i - j >= 0) {
    //             // cout << i << " : " << j << " = " << i-j << "\n";
    //             // cout << dp[i] << " : " << dp[i-j] << "\n";
    //             dp[i] += dp[i-j];
    //         }
    //     }
    // }

    // for(i=0;i<=n;i++) {
    //     cout << dp[i] << " ";
    // }
    // cout << "\n";

    int dp[6] = {1, 2, 4, 8, 16, 32};
    if(n <= 6) {
        cout << dp[n-1] << "\n";
        return;
    }

    vector<vector<ll>> inm = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1}
    };
    vector<vector<ll>> ansMat = matExp(inm, n - 6);
    // cout << "ans : \n";
    // for(i=0;i<6;i++) {
    //     for(j=0;j<6;j++) {
    //         cout << ansMat[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    int ans = 0;
    for(i=0;i<6;i++) {
        ans = (1ll * ans + ansMat[5][i] * dp[i]) % mod;
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