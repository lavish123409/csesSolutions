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
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#endif
 
// tip: try to think about recursive solutions for Mathematical problems
// sometimes it becomes too complex to use just 1 formula to calculate complete answer
 
/*
 
    I approach
    we can count the number of divisors for a number x in O(sqrt(nx)) time
    because we only need to traverse sqrt(x) numbers to find first divisors and rest of them would be number / first_divisor
    but we cannot do this for n numbers, because complexity would be O(n*x*sqrt(x))
    so, we would have to pre calculate for n numbers in array and answer queries for n numbers in O(1) time

    RE1 
    Didn't realised that maximum number which can come as input is 1e6, so MAXN dould be 1e6
    but increasing that would increase our time for precalculation
    also realised that precalculation is uneccessary
    the complexity of complete algorithm without precalculation would be O(n*sqrt(x)) and not O(n*x*sqrt(x))

*/
string ps = "\n";

const int MAXN = 1e6+5;
int nod[MAXN];

int getNumberOfDivisors(int n) {
    int i, ans=0;
    for(i=1;i*i <= n; i++) {
        // debug(n, i);
        if(n % i == 0) {
            ans++;
            if(i != n/i) {
                ans++;
            }
        }
        // debug(ans);
    }

    return ans;
}

void solve() {
    int i, n;
    cin >> n;
    debug(n);
    // int nod[MAXN] = {0};

    // for(i=1;i<MAXN;i++) {
    //     nod[i] = getNumberOfDivisors(i);
    //     // if(i < 100) {
    //     //     int cnod = getNumberOfDivisors(i);
    //     //     debug(i, nod[i], cnod);
    //     // }
    // }
    // debug(getNumberOfDivisors(18));

    while(n--) {
        int x;
        cin >> x;
        debug(x);

        // cout << nod[x] << "\n";
        cout << getNumberOfDivisors(x) << "\n";
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