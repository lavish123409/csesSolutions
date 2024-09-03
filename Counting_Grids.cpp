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
    we can use burnside lemma for this which states that (number of unique arrangements) = (sum of all arrangements which are similar under symmetry i) / (total number of symmetries)
    in this case, the total number of symmetries or we can say rotations is 4, i.e, 0deg, 90deg, 180deg, and 270deg

    - for 0deg, the number of all arrangements which are similar to original arrangement would be any arrangement in the matrix
        so, in total all arrangements for any matrix would be 2^{(rows) * (columns)} = 2^(n*n)

    - for 180 deg, the number of all arrangements which are similar to original arrangement would be 
        - if n is even, for n/2 rows we can choose any value from 2 values, and the number of elements in next n/2 rows would be based on already chosen values
        - for ex, for n=4
            2 2 2 2
            2 2 2 2
            1 1 1 1 
            1 1 1 1
        here, (0,0) should be similar to (3,3), (0,1) should be similar to (3,2), (0,2) should be similar to (3,1), etc.
        - so, in total all arrangements for any matrix would be 2^{(rows/2) * (columns)} = 2^((n/2)*n)

        - if n is odd, for n/2 rows we can choose any value from 2 values, and the number of elements in next n/2 rows would be based on already chosen values
        - and for middle row, the first element should be similar to last element, the second element should be similar to second last element, and so on till middle element which would be similar to itself
        - for ex, for n=5
            2 2 2 2 2
            2 2 2 2 2
            2 2 2 1 1
            1 1 1 1 1
            1 1 1 1 1
        here, (2,0) should be similar to (2,4), (2,1) should be similar to (2,3), (2,2) should be similar to (2,2), etc.
        - so, in total all arrangements for any matrix would be 2^{(rows/2) * (columns) + ceil(rows/2)} = 2^((n/2)*n + (n+1)/2)

    - for 90 deg, the number of all arrangements which are similar to original arrangement would be 
        - if n is even
            - for first row, (0,0) == (0, n-1), (0,1) == (1,n-1), (0,2) == (2,n-1) and so on till (0, n-2) == (n-2, n-1) and (0,0) == (0, n-1) == (n-1, n-1)
            - for second row, (1,0) == (0, n-2), (1,2) == (1,n-2), (1,2) == (2,n-2) and so on
            - and so on
        - for ex, for n=4
            2 2 2 1
            1 2 1 1
            1 1 1 1 
            1 1 1 1
        - we would get sequence like 1 + 3 + 5 + ... = 2*chf-1 + 2*(chf+1)-1 + 2*(chf+2)-1 ..., where chf = ceil(n/2)
        - if we would solve it, we would the sum as chf^2
        - so, in total all arrangements for any matrix would be 2^{ceil(rows/2)^2} = 2^(((n+1)/2)^2)

        - if n is odd
            - for first row, (0,0) == (0, n-1), (0,1) == (1,n-1), (0,2) == (2,n-1) and so on till (0, n-2) == (n-2, n-1) and (0,0) == (0, n-1) == (n-1, n-1)
            - for second row, (1,0) == (0, n-2), (1,2) == (1,n-2), (1,2) == (2,n-2) and so on
            - and so on
        - we would have to count middle element also which would be similar to itself
        - for ex, for n=5
            2 2 2 2 1
            1 2 2 1 1
            1 1 2 1 1
            1 1 1 1 1
            1 1 1 1 1
                                    here, this one is for the middle element
                                     |
        - we would get sequence like 1 + 2 + 4 + 6 + ... = 1 + 2*chf + 2*(chf+1) + 2*(chf+2) ..., where chf = ceil(n/2) + 1
        - if we would sum it, we would get chf^2 + chf + 1
        - so, in total all arrangements for any matrix would be 2^{chf^2 + chf + 1}, where chf = ceil(n/2) - 1

    - for 270 deg, the number of all arrangements which are similar to original arrangement would be similar to 90deg

    we can sum all of them and at last multiply the result by inverse of 4

    WA1
    realised that for 180deg in odd case, second half of middle row would be similar to first half

    WA2
    realised that in power of 2, we should mod it by mod-1

    Solution
    explanation ->  https://codeforces.com/blog/entry/82103?#comment-833959

    
*/
string ps = "\n";

const int mod = int(1e9+7);

int pwr(int b, int e) {
    debug(b, e);
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

void solve() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << "2\n";
        return;
    }

    int chf = (n + 1) / 2;
    debug(chf);
    int ans = 0;

    ans = pwr(2, (1ll * n * n) % (mod - 1));
    // debug(ans);
    // if(n&1) {
    //     ans = (1ll * ans + pwr(2, (1ll * n * (chf - 1) + chf) % (mod - 1))) % mod;
    // }
    // else {
    //     ans = (1ll * ans + pwr(2, (1ll * n * chf) % (mod - 1))) % mod;
    // }
    // debug(ans);
    // if(n&1) {
    //     chf--;
    //     ans = (1ll * ans + pwr(2, ((1ll * chf * chf) % (mod - 1) + chf + 2) % (mod - 1))) % mod;
    // }
    // else {
    //     ans = (1ll * ans + pwr(2, ((1ll * chf * chf) % (mod - 1) + 1) % (mod - 1))) % mod;
    // }
    if(n&1) {
        ans = (1ll * ans + pwr(2, ((1ll * n * n - 1) / 2 + 1) % (mod-1))) % mod; // for 180deg
        ans = (1ll * ans + pwr(2, ((1ll * n * n - 1) / 4 + 2) % (mod-1))) % mod; // for 90 and 270deg
    }
    else {
        ans = (1ll * ans + pwr(2, ((1ll * n * n) / 2) % (mod-1))) % mod; // for 180deg
        ans = (1ll * ans + pwr(2, ((1ll * n * n) / 4 + 1) % (mod-1))) % mod; // for 90 and 270deg
    }

    ans = (1ll * ans * inv(4)) % mod;
    debug(ans);
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